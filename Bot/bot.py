from telegram import Update, InlineKeyboardButton, InlineKeyboardMarkup, Bot
from telegram.ext import Application, CommandHandler, MessageHandler, filters, CallbackQueryHandler, ConversationHandler, ContextTypes
from telegram.error import Forbidden, NetworkError, TimedOut, Conflict


from urllib.parse import urlparse       # Para analizar URLs
import re                               # Para expresiones regulares
from datetime import datetime, timedelta# Para se encarga der fechas
import os                               # Para se encarga der archivos
import httpx
import traceback
import asyncio

# Para trabajar con .env
from dotenv import load_dotenv

load_dotenv()

# Para enviar correos electrónicos de GMAIL
from google.auth.transport.requests import Request
from google.oauth2.credentials import Credentials
from google_auth_oauthlib.flow import InstalledAppFlow
from googleapiclient.discovery import build
from googleapiclient.errors import HttpError
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.mime.base import MIMEBase
from email import encoders
import base64
import mimetypes

#Modificaciones para añadir funcionalidad para generar los enunciados con IA
from google import genai
from google.genai import types
import asyncio
import pathlib
# Definimos los estados de la conversación

MENU, CURSO, ASIGNATURA, DESCRIPCION, ARCHIVOS, CONTACTO, MATERIAL_ENLACE, CAPTURA, CORRECCION, ANIO_EXAMEN, PROFESOR_EXAMEN, ES_DEPARTAMENTO_EXAMEN, GRADO_EXAMEN, GRUPO_EXAMEN, FECHA_EXAMEN, DURACION_EXAMEN, MENU_OTRO, FORMA_AYUDA, PETICION_ASIGNATURA, PASSWD, NOTIFICACION, NOTIFICACION_PROCESAR, ESCANEO, RECUPERAR_METADATOS = range(24)

# Token del bot
TOKEN=os.getenv("TELEGRAM_TOKEN")
NOTIFICATION_PASSWORD = ""
ADMINS_IDS = []

# Define el directorio donde guardarás los archivos
DOWNLOAD_BASEDIR = os.getenv("DOWNLOAD_BASEDIR")
PLANTILLAS_BASEDIR = os.path.join(DOWNLOAD_BASEDIR, "plantillas_ia")

# Por si cambiaran los nombres de estos archivos, solo hace falta modificarlos aqui
PREAMBULO = "preambulo.tex"
PLANTILLA_EXAMEN = "Plantilla_Ex.tex"
PROMPT = "prompt_ocr.tex"

LOG_PATH = os.path.join(DOWNLOAD_BASEDIR, "log_file.log")
CHAT_IDS_PATH = os.path.join(DOWNLOAD_BASEDIR, "chat_ids.log")

# Rutas para los archivos que requiere la transcripción con IA
PREAMBULO_PATH = os.path.join(PLANTILLAS_BASEDIR,PREAMBULO)
PLANTILLA_PATH = os.path.join(PLANTILLAS_BASEDIR,PLANTILLA_EXAMEN)
# Aquí poner en vez de download basedir, donde sea que se quiera poner el txt del prompt
PROMPT_PATH = os.path.join(DOWNLOAD_BASEDIR, PROMPT)

# Valor por defecto de notificar
DEFAULT_NOTIFY = True
SEPARATOR = ";"

# Constantes para los callback data del menú principal
CALLBACK_NUEVO = 'Nuevo material'
CALLBACK_COMPLEMENTAR = 'Complementar material existente'
CALLBACK_CORREGIR = 'Correccion'
CALLBACK_OTRO = 'Otro'
CALLBACK_EXAMEN = 'Examen'
CALLBACK_COLABORAR = 'Colaborar pasando a ordenador'
CALLBACK_ESCANEO = 'Escanear examen con IA'

# Constantes para los callback data del menú de OTRO
CALLBACK_LINK = 'enlace'
CALLBACK_FILES = 'archivos'
CALLBACK_SCREENSHOTS = 'capturas'
CALLBACK_DESCRIPTION = 'descripcion'
CALLBACK_END = 'terminar'

# Constantes para los callback del menú de notify
CALLBACK_NOTIFICAR = 'notificar'
CALLBACK_NO_NOTIFICAR = 'no_notificar'

# Claves para el diccionario con los datos dados por el el usuario
USERNAME_KEY = 'Username'
NAME_KEY = 'Nombre'
LAST_NAME_KEY = 'Apellidos'
INIT_TIME_KEY = 'Hora de Inicio'
END_TIME_KEY = 'Hora de Fin'
DOWNLOADS_DIR_KEY = 'Directorio de Descargas'
EMAIL_KEY = 'Email'
PHONE_KEY = 'Telefono'
CHATID_KEY = 'Chat ID'

OPTION_KEY = 'Opción elegida'
CURSO_KEY = 'Curso'
SUBJECT_KEY = 'Asignatura'
DESCRIPTION_KEY = 'Descripcion'
LINK_KEY = 'Material referenciado'
SCREENSHOT_KEY = 'Capturas'
FILES_KEY = 'Archivos'
CORRECTION_KEY = 'Correccion'
AYUDA_KEY = 'Forma de ayuda'

YEAR_KEY = 'Año del examen'
PROFESSOR_KEY = 'Profesor del examen'
GRADO_KEY = 'Grado del examen'
GROUP_KEY = 'Grupo del examen'
DATE_EX_KEY = 'Fecha del examen'
DURATION_KEY = 'Duracion del examen'
IS_DEPARTMENT_KEY = '¿Lo ha puesto el departamento?'


# Comando para indicar que no sé una información de un examen
UNKNOWN_COMMAND = '/desconocido'
TODAY_COMMAND = '/today'
ACTUAL_COMMAND = '/cursoActual'

subjects = {
    "1": ["Geometría I", "Álgebra I", "Cálculo I", "FP", "FFT", "TOC", "Cálculo II", "Geometría II", "MN I", "EDIP", "MP", "FS"],
    "2": ["Análisis I", "EC", "ED", "Geometría III", "SO", "Topología I", "Algorítmica", "Análisis II", "AC", "LMD", "Modelos I", "PDOO"],
    "3": ["Ec. Dif. I", "FR", "FBD", "MC", "Probabilidad", "SCD", "FIS", "ISE", "IA", "MN II", "VC I", "Álgebra II"],
    "4": ["Análisis Funcional", "DDSI", "Inferencia", "IG", "Topología II", "Álgebra III", "Curvas y Superficies", "Ec. Dif. II", "Modelos II"],
    "5": ["IES"]
}


# Constantes para evitar que se excedan las peticiones al servidor
TIME_LIMIT = 60             # Limite de tiempo para REQUESTS_LIMIT peticiones
REQUESTS_LIMIT = 3          # Limite de peticiones en TIME_LIMIT segundos
FILES_LIMIT = 10            # Limite de archivos en una petición
SCREENSHOTS_LIMIT = 5       # Limite de capturas en una petición


'''
En el caso de CALLBACK_NUEVO:
1. Se solicita el curso
2. Se solicita la asignatura
3. Se solicita la descripción
4. Se solicitan los archivos
5. Se solicita el contacto (si no tiene username)

En el caso de CALLBACK_COMPLEMENTAR:
1. Se solicita el curso
2. Se solicita la asignatura
3. Se solicita el enlace del material
4. Se solicita la descripción
5. Se solicitan los archivos
6. Se solicita el contacto (si no tiene username)

En el caso de CALLBACK_CORREGIR:
1. Se solicita el curso
2. Se solicita la asignatura
3. Se solicita el enlace del material
4. Se solicita la captura
5. Se solicita la corrección
6. Se solicita el contacto (si no tiene username)

En el caso de CALLBACK_OTRO:
1. Hay un menu para ver que desea:
    - Hacer referenciara a un documento de la web (enlace)
    - Añadir archivos
    - Añadir capturas
    - Añadir descripción
    - Terminar
  Este menú se puede repetir las veces que se desee
2. Se solicita el contacto (si no tiene username)

En el caso de CALLBACK_EXAMEN:
1. Se solicita el curso
2. Se solicita la asignatura
3. Se solicita el año del examen
4. Se solicita el profesor que redactó el examen
5. Se pregunta mediante un botón si el examen lo redactó el departamento o no
6. Se solicita el grado (puede ser del DGIIM, de Matemáticas, o de Informática).
7. Se solicita el grupo
8. Se solicita la fecha del examen
9. Se solicita la descripción del examen (Parciales, Convocatoria ordinaria, Extraordinaria, etc.)
10. Se solicita la duración del examen
11. Se solicita el archivo del examen
12. Se solicita el contacto (si no tiene username)
- En el caso de que alguna información no se sepa, contestar con /desconocido (UNKNOWN_COMMAND)

En el caso de CALLBACK_COLABORAR:
1. Se solicita la forma en la que desea colaborar (Latex, Markdown, etc.)
2. Se solicita el contacto (si no tiene username)

'''


"""
Comprueba si un número de teléfono es válido.

Args:
    numero (str): Número de teléfono a validar.

Returns:
    bool: True si el número es válido, False en caso contrario.
"""
def es_numero_telefono(numero):
    

    # Quito los espacios en blanco y guiones
    numero = numero.replace(" ", "").replace("-", "")

    # Expresión regular para validar número de teléfono español
    # - Puede tener prefijo internacional (+34) o no
    # - Empieza por 6, 8 o 9 y tiene 9 dígitos
    patron_espanol = re.compile(r'^(\+34)?([689]\d{8})$')
    
    # Expresión regular para validar número de teléfono internacional (general)
    # - Empieza por un prefijo internacional (+) y tiene al menos 1 dígito
    patron_internacional = re.compile(r'^\+\d{1,4}\d+')
    
    # Comprobar si el número coincide con el patrón español o internacional
    if patron_espanol.match(numero) or patron_internacional.match(numero):
        return True
    return False

"""
Comprueba si un correo electrónico es válido.

Args:
    email (str): Correo electrónico a validar.

Returns:
    bool: True si el correo es válido, False en caso contrario.
"""
def es_email(email):
    # Expresión regular para validar el formato básico del correo electrónico
    patron = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
    
    # Verificar si el correo electrónico cumple con el formato básico
    if re.match(patron, email):
        return True
    else:
        return False


"""
Comprueba si una URL es un enlace válido.

Args:
    url (str): URL a validar.

Returns:
    bool: True si la URL es válida, False en caso contrario.
"""
def es_enlace(url: str) -> bool:
    try:
        # Asegurarse de que la URL tenga un esquema
        if not (url.startswith('http://') or url.startswith('https://')):
            # Si no tiene esquema, agregar `http://` por defecto
            url = 'http://' + url
        
        # Analizar la URL
        parsed_url = urlparse(url)
        
        return True
    except Exception as e:
        add_log(LOG_PATH, f"Error al analizar la URL {url}: {e}")
        return False
  
"""
Obtiene la hora actual en formato 'YYYY-MM-DD_HH:MM:SS'.

Returns:
    str: Hora actual en formato 'YYYY-MM-DD_HH:MM:SS'.
"""
def get_hora_str():
    return datetime.now().strftime("%Y-%m-%d_%H:%M:%S")

"""
Obtiene la hora actual en formato 'YYYY-MM-DD_HH:MM:SS'.

Returns:
    str: Hora actual en formato 'DD/MM/YYYY'.
"""
def get_fecha_str():
    return datetime.now().strftime("%d/%m/%Y")


"""
Añade un mensaje al archivo de log.

Args:
    file (str): Ruta del archivo de log.
    msg (str): Mensaje a añadir al log.
"""
def add_log(file: str, msg: str):

    # Abrimos el archivo en modo append
    with open(file, "a") as f:
        f.write(f"{get_hora_str()}\t- {msg}\n")



def register_chat_id(file: str, chat_id):
    """
    Registra un chat_id en el archivo de chat_ids.

    Args:
        file (str): Ruta del archivo de chat_ids.
        chat_id (int): ID del chat a registrar.
    """
    # Comprobar si el chat_id ya está registrado
    with open(file, "r") as f:
        lines = f.read().splitlines()

    # Vemos si el chat_id ya está registrado
    ya_registrado = False
    for line in lines:
        if str(chat_id) == line.strip().split(SEPARATOR)[0]:
            ya_registrado = True
            break
    
    
    if not ya_registrado:
        # Si no está registrado, añadirlo al archivo
        with open(file, "a") as f:
            f.write(f"{chat_id}{SEPARATOR}{DEFAULT_NOTIFY}\n")
            add_log(LOG_PATH, f"Chat_id {chat_id} registrado correctamente.")
    

"""
Función que se encarga de controlar que no se excedan las peticiones en un tiempo determinado.

El límite de peticiones es de REQUESTS_LIMIT en un intervalo de TIME_LIMIT segundos.
"""
def has_exceeded_requests(context: ContextTypes.DEFAULT_TYPE) -> bool:
    # Sabiendo que el formato de las carpetas creadas es el siguiente:
    #   - %Y-%m-%d_%H:%M:%S_username
    # Contar cuántas carpetas hay en menos de 60 segundos
    # para saber si se ha excedido el límite de peticiones
    
    # Obtener la hora de la carpeta actual
    act_time = datetime.strptime(context.user_data[INIT_TIME_KEY], "%Y-%m-%d_%H:%M:%S")

    # Contar cuántas carpetas hay en menos de TIME_LIMIT segundos
    requests = 1 # Inicializar a 1 porque ya hay una carpeta (la que queremos procesar)


    # Guardamos las líneas de los últimos TIME_LIMIT segundos
    with open(LOG_PATH, "r") as f:
        lines = f.readlines()

    # Recorrer las líneas del log desde el final
    for line in reversed(lines):
        # Obtener la hora de la línea. Si la línea no tiene el formato esperado, se ignora
        try:
            line_time = datetime.strptime(line.strip().split("\t")[0], "%Y-%m-%d_%H:%M:%S")
        except ValueError:
            continue
        
        # Si la diferencia de tiempo es mayor a TIME_LIMIT, salir del bucle
        if act_time - line_time > timedelta(seconds=TIME_LIMIT):
            break

        # Antes de contabilizarla, comprobamos que es del usuario actual
        if get_userIdentifier(context.user_data) in line:
            
            # Comprobar si la línea describe que se ha iniciado una petición o se ha excedido el límite
            if "iniciada" in line or "excedido" in line:
        
                # Incrementar el contador de peticiones
                requests += 1
    
    return requests > REQUESTS_LIMIT


"""
Funcion que determina si un usuario es contactable.
Un usuario es contactable si tiene un username, un correo o un número de teléfono.
"""
def es_contactable(datos: dict) -> bool:
    return      datos.get(USERNAME_KEY) is not None \
            or  datos.get(EMAIL_KEY)    is not None \
            or  datos.get(PHONE_KEY)    is not None


"""
Función que obtiene el identificador del usuario.

Args:
    datos (dict): Datos del usuario.

Returns:
    str: Identificador del usuario.
"""
def get_userIdentifier(datos: dict) -> str:
    if datos is None:
        return "Usuario sin nombre"
    return datos.get(USERNAME_KEY) or datos.get(NAME_KEY) or datos.get(CHATID_KEY) or "Usuario sin nombre"




"""
Funcion que se ejecuta al inicio de la conversación.

Returns:
    int: Nuevo estado de la conversación. MENU
"""
async def start(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:

    # Guardamos información del usuario
    context.user_data[USERNAME_KEY] = update.message.from_user.username
    context.user_data[NAME_KEY] = update.message.from_user.first_name
    context.user_data[LAST_NAME_KEY] = update.message.from_user.last_name
    context.user_data[INIT_TIME_KEY] = get_hora_str()
    context.user_data[CHATID_KEY] = update.message.chat_id

    # Comprobar si el usuario ha excedido el límite de peticiones
    if has_exceeded_requests(context):
        add_log(LOG_PATH, f"El usuario {get_userIdentifier(context.user_data)} ha excedido el límite de peticiones.")
        await update.message.reply_text(
            f"Has excedido el límite de {REQUESTS_LIMIT} peticiones en {TIME_LIMIT} segundos. Por favor, inténtalo de nuevo más tarde."
        )
        context.user_data.clear()
        return ConversationHandler.END
    
    # Log de conv iniciada. Fecha + mensaje
    add_log(LOG_PATH, f"Peticion iniciada por {get_userIdentifier(context.user_data)}. Chat ID: {update.message.chat_id}.")
    register_chat_id(CHAT_IDS_PATH, update.message.chat_id)
    

    # Modificamos la carpeta en la que se va a guardar todo.
    # Esta será el BASEDIR + hora_inicio + get_userIdentifier
    file_name = context.user_data[INIT_TIME_KEY] + "_" + get_userIdentifier(context.user_data)
    context.user_data[DOWNLOADS_DIR_KEY] = os.path.join(DOWNLOAD_BASEDIR, file_name)
    os.makedirs(context.user_data[DOWNLOADS_DIR_KEY])

    # Mensaje de bienvenida
    await update.message.reply_text(
        "¡Bienvenido! Gracias por colaborar con LosDelDGIIM.github.io.\n"
        "En cualquier momento puedes cancelar la operación con /cancel.\n"
        "Si necesitas ayuda, escribe /help.\n"
        "¿En qué te gustaría colaborar?",
        reply_markup=InlineKeyboardMarkup([
            [InlineKeyboardButton("Añadir nuevo material", callback_data=CALLBACK_NUEVO)],
            [InlineKeyboardButton("Complementar el material existente", callback_data=CALLBACK_COMPLEMENTAR)],
            [InlineKeyboardButton("Corrección de erratas", callback_data=CALLBACK_CORREGIR)],
            [InlineKeyboardButton("Examen", callback_data=CALLBACK_EXAMEN)],
            [InlineKeyboardButton("Colaborar pasando a digital", callback_data=CALLBACK_COLABORAR)],
            #[InlineKeyboardButton("Escanear examen a LaTeX (IA)", callback_data=CALLBACK_ESCANEO)],
            [InlineKeyboardButton("Otro", callback_data=CALLBACK_OTRO)]
        ])
    )
    return MENU



"""
Función que se encarga de la selección del menú principal.

Returns:
    int: Nuevo estado de la conversación.
            - CURSO si se selecciona NUEVO, COMPLEMENTAR, CORREGIR o EXAMEN
            - MENU_OTRO si se selecciona OTRO
"""
async def menu_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    query = update.callback_query
    await query.answer()
    context.user_data[OPTION_KEY] = query.data

    # Enviar un mensaje informando de la opción seleccionada (no espera respuesta)
    if context.user_data[OPTION_KEY] == CALLBACK_NUEVO:
        await query.message.reply_text(
            "Has elegido añadir nuevo material, ¡gracias!\n"
            "Recuerda que, para que se suba, debe ser material de calidad (por ejemplo, que no sean apuntes tomados a mano), y que siga la plantilla de la web (disponible en el repositorio).\n"
            "En el caso de que se trate de un examen pasado a digital, rellenar conforme sea posible el profesor, grado, grupo, duración, fecha, etc."
        )
    
    elif context.user_data[OPTION_KEY] == CALLBACK_COMPLEMENTAR:
        await query.message.reply_text(
            "Has elegido complementar material existente, ¡gracias!\n"
            "Aporta la información lo más detallada posible, para que nos sea más fácil añadirlo."
        )

    elif context.user_data[OPTION_KEY] == CALLBACK_CORREGIR:
        await query.message.reply_text(
            "Has elegido corregir erratas, ¡gracias!\n"
            "Por favor, ten en cuenta que puede ser que cursásemos esta asignatura hace tiempo y no recordemos bien el contenido, detalla lo máximo posible el error."
        )
    
    elif context.user_data[OPTION_KEY] == CALLBACK_EXAMEN:
        await query.message.reply_text(
            "Has elegido colaborar con un examen, ¡gracias!\n"
            "-\tEn el caso de exámenes pasados a digital, escribir /cancel para volver a inicar, y elegir *añadir nuevo material*.\n"
            "-\tEn el caso de exámenes que no se hayan pasado a digital, sí es aquí.\n"
            "Por favor, proporciona toda la información que puedas, para que podamos añadirlo a la web.\n"
            f"Si no sabes alguna información, puedes responder con {UNKNOWN_COMMAND}.\n"
            "Además, te animamos a pasarlo a digital si tienes la oportunidad, ¡nos ayudarías mucho!"
        )
    
    elif context.user_data[OPTION_KEY] == CALLBACK_OTRO:
        await query.edit_message_text(
            "Has elegido una opción diferente, ya que las anteriores no describen su situación.\n" + \
            "En el caso de que este formulario no se ajuste a tu petición, recuerda que puedes escribirnos un correo directamente tal y como se indica en la web LosDelDGIIM.github.io/colaboracion.html."
        )

    elif context.user_data[OPTION_KEY] == CALLBACK_COLABORAR:
        await query.message.reply_text(
            "Has elegido colaborar pasando a digital, ¡gracias!\n"
            "Por ejemplo, hay compañeros que nos pasan fotos de exámenes, pero necesitamos que alguien los pase a digital.\n"
            "Por favor, indica con qué nos puedes ayudar (Latex, Markdown, programación, etc.)\n"
            "Nos pondremos en contacto contigo para informarte de cómo puedes colaborar."
        )
    """
    elif context.user_data[OPTION_KEY] == CALLBACK_ESCANEO:
        context.user_data['FOTOS_IA'] = []

        # Se llama a la función para actualizar las plantillas cada vez que se hace una petición
        try:
            actualizar_plantillas_desde_github()
        except Exception as e:
            os.system(f"rm -rf {context.user_data.get(DOWNLOADS_DIR_KEY)}")
            raise
        await query.message.reply_text(
            "Sube una foto clara del examen que quieres pasar a código LaTeX.\n"
            "Recomendamos el uso de esta herramienta fuera del horario 14:00-22:00 ya que los servidores sufren mayor demanda en dichas horas.")
        return ESCANEO"""
    #######################################


    if context.user_data[OPTION_KEY] in [CALLBACK_NUEVO, CALLBACK_COMPLEMENTAR, CALLBACK_CORREGIR, CALLBACK_EXAMEN]:
        # Solicitar el curso
        await solicitar_curso(query)
        return CURSO

    elif context.user_data[OPTION_KEY] == CALLBACK_OTRO:
        # Menú de OTRO
        await solicitar_menu_otro(query, context)
        return MENU_OTRO
    
    elif context.user_data[OPTION_KEY] == CALLBACK_COLABORAR:
        return FORMA_AYUDA

"""
Función que se encarga de registrar de qué forma quiere el usuario colaborar.

Returns:
    int: Nuevo estado de la conversación. CONTACTO o TERMINAR
"""
async def forma_ayuda_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    context.user_data[AYUDA_KEY] = update.message.text
    if not es_contactable(context.user_data):
        await update.message.reply_text("Por favor, proporciona un correo o número de teléfono de contacto (tan solo uno).\n\nTen en cuenta que se te solicitará cada vez que termines una colaboración, puesto que no dispones de username. Para evitar esto, puedes configurar un username en Telegram.")
        return CONTACTO
    else:
        return await terminar_handler(update, context)

"""
Función que se encarga de la selección del menú de OTRO.
Tan solo aparecen las opciones que no se han completado.

No devuelve nada, tan solo muestra el menú de opciones.
"""
async def solicitar_menu_otro(query, context: ContextTypes.DEFAULT_TYPE) -> None:
    keyboard = []

    if LINK_KEY not in context.user_data:
        keyboard.append([InlineKeyboardButton("Referenciar material (enlace)", callback_data=CALLBACK_LINK)])
    
    if FILES_KEY not in context.user_data:
        keyboard.append([InlineKeyboardButton("Aportar archivos", callback_data=CALLBACK_FILES)])
    
    if SCREENSHOT_KEY not in context.user_data:
        keyboard.append([InlineKeyboardButton("Aportar capturas", callback_data=CALLBACK_SCREENSHOTS)])
    
    if DESCRIPTION_KEY not in context.user_data:
        keyboard.append([InlineKeyboardButton("Añadir una descripción", callback_data=CALLBACK_DESCRIPTION)])

    keyboard.append([InlineKeyboardButton("Terminar", callback_data=CALLBACK_END)])

    if len(keyboard) > 1:
        await query.message.reply_text(
            "Por favor, selecciona una opción:",
            reply_markup=InlineKeyboardMarkup(keyboard)
        )

    # Ya se han usado todas las opciones, tan solo se puede terminar    
    else:
        if not es_contactable(context.user_data):
            await query.message.reply_text("Por favor, proporciona un correo o número de teléfono de contacto (tan solo uno).\n\nTen en cuenta que se te solicitará cada vez que termines una colaboración, puesto que no dispones de username. Para evitar esto, puedes configurar un username en Telegram.")
            return CONTACTO
        else:
            return await terminar_handler(query, context)

"""
Función que se encarga de la selección del curso.

No devuelve nada, tan solo muestra las distintas opciones.
"""
async def solicitar_curso(query):
    await query.message.reply_text(
        "Por favor, selecciona el curso:",
        reply_markup=InlineKeyboardMarkup([
            [InlineKeyboardButton("Primero (1º)", callback_data='1')],
            [InlineKeyboardButton("Segundo (2º)", callback_data='2')],
            [InlineKeyboardButton("Tercero (3º)", callback_data='3')],
            [InlineKeyboardButton("Cuarto (4º)", callback_data='4')],
            [InlineKeyboardButton("Quinto (5º)", callback_data='5')],
            [InlineKeyboardButton("Optativas", callback_data='Optativas')],
            [InlineKeyboardButton("Desconocido", callback_data='Desconocido')]
        ])
    )


"""Función que se encarga de solicitar la asignatura.
No devuelve nada, tan solo muestra las distintas opciones.
Args:
    query (CallbackQuery): Consulta del usuario.
    curso (str): Curso seleccionado por el usuario.
"""
async def solicitar_asignatura(query, curso):
    asignaturas = subjects.get(curso, [])
    opciones = []

    # Calcular el punto medio
    mitad = (len(asignaturas) + 1) // 2

    # Rellenar las columnas
    col_izq = asignaturas[:mitad]
    col_der = asignaturas[mitad:]

    # Construir filas de dos columnas
    for i in range(mitad):
        fila = []
        fila.append(InlineKeyboardButton(col_izq[i], callback_data=col_izq[i]))
        if i < len(col_der):
            fila.append(InlineKeyboardButton(col_der[i], callback_data=col_der[i]))
        opciones.append(fila)

    opciones.append([InlineKeyboardButton("Otra asignatura", callback_data="Otra")])
    await query.message.reply_text(
        "Por favor, selecciona la asignatura:",
        reply_markup=InlineKeyboardMarkup(opciones)
    )

    



"""
Función que se encarga de la selección de las opciones del menú de OTRO.

Returns:
    int: Nuevo estado de la conversación. 
            - MATERIAL_ENLACE si se selecciona enlace
            - ARCHIVOS si se selecciona archivos
            - CAPTURA si se selecciona capturas
            - DESCRIPCION si se selecciona descripción
            - CONTACTO si se selecciona terminar y no tiene username, terminar en caso contrario.

"""
async def menu_otro_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    query = update.callback_query
    await query.answer()
    opcion = query.data

    if opcion == CALLBACK_LINK:
        await query.message.reply_text(
            "Has elegido referenciar cierto material.\n"
            "Para ello, por favor, proporciona el enlace al material."
        )
        return MATERIAL_ENLACE

    elif opcion == CALLBACK_FILES:
        context.user_data[FILES_KEY] = []
        await query.message.reply_text(
            "Has elegido aportar archivos. "
            "Por favor, sube los archivos en cuestión.\n"
            "Puedes subir tantos archivos como desees.\n"
            "Para terminar, introduce /finarchivos."
        )
        return ARCHIVOS

    elif opcion == CALLBACK_SCREENSHOTS:
        context.user_data[SCREENSHOT_KEY] = []
        await query.message.reply_text(
            "Por favor, sube una captura. "
            "Puedes subir tantas como desees. Para terminar, introduce /fincapturas. "
            "Tienen que ser imágenes directamente, no documentos (aunque tengan formato de imagen)."
        )
        return CAPTURA

    elif opcion == CALLBACK_DESCRIPTION:
        await query.message.reply_text("Has elegido añadir una descripción. Por favor, describe lo que necesites.")
        return DESCRIPCION

    elif opcion == CALLBACK_END:
        if not es_contactable(context.user_data):
            await query.message.reply_text("Por favor, proporciona un correo o número de teléfono de contacto (tan solo uno).\n\nTen en cuenta que se te solicitará cada vez que termines una colaboración, puesto que no dispones de username. Para evitar esto, puedes configurar un username en Telegram.")
            return CONTACTO
        else:
            return await terminar_handler(query, context)


"""
Función que se encarga de la selección del curso.

Returns:
    int: Nuevo estado de la conversación. ASIGNATURA
"""
async def curso_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    query = update.callback_query
    await query.answer()
    context.user_data[CURSO_KEY] = query.data

    if context.user_data[CURSO_KEY] not in ['1', '2', '3', '4', '5']:
        await query.message.reply_text("Por favor, escribe el nombre de la asignatura.")
        return PETICION_ASIGNATURA

    # Solicitar la asignatura
    await solicitar_asignatura(query, context.user_data[CURSO_KEY])
    return ASIGNATURA

"""
Función que se encarga de la selección de la asignatura.

Returns:
    int: Nuevo estado de la conversación.
            - DESCRIPCION si se selecciona NUEVO, COMPLEMENTAR
            - MATERIAL_ENLACE si se selecciona CORREGIR
            - ANIO_EXAMEN si se selecciona EXAMEN
"""
async def asignatura_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    query = update.callback_query
    await query.answer()
    context.user_data[SUBJECT_KEY] = query.data

    if context.user_data[SUBJECT_KEY] == "Otra":
        await query.message.reply_text("Por favor, escribe el nombre de la asignatura.")
        return PETICION_ASIGNATURA

    return await post_asignatura_handler(update, context)

async def peticion_asignatura_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    # Guardar la asignatura introducida por el usuario
    context.user_data[SUBJECT_KEY] = update.message.text

    return await post_asignatura_handler(update, context)



async def post_asignatura_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    # Detecta si viene de mensaje de texto o de callback
    msg = update.message if update.message else update.callback_query.message

    if context.user_data[OPTION_KEY] == CALLBACK_NUEVO:
        await msg.reply_text("Por favor, describe lo que se va a añadir.")
        return DESCRIPCION
    
    elif context.user_data[OPTION_KEY] in [CALLBACK_COMPLEMENTAR, CALLBACK_CORREGIR]:
        tmp = "complementar" if context.user_data[OPTION_KEY] == CALLBACK_COMPLEMENTAR else "corregir"
        await msg.reply_text(
            f"Por favor, proporciona el enlace al material que se va a {tmp}.\n"
            f"En caso de no querer subir enlace, contestar con /noenlace, pero tendrá entonces que describir bien el material que va a {tmp}."
        )
        return MATERIAL_ENLACE

    elif context.user_data[OPTION_KEY] == CALLBACK_EXAMEN:
        await msg.reply_text(f"Por favor, indica el curso académico del examen (p.ej. 2023/2024).\nSi es el actual, puedes contestar con {ACTUAL_COMMAND}.\n(En caso de no saberlo, contestar con {UNKNOWN_COMMAND}).")
        return ANIO_EXAMEN


"""
Función que se encarga de la respuesta del enlace del material.

Returns:
    int: Nuevo estado de la conversación. PROFESOR_EXAMEN

"""
async def anio_examen_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    
    # Comprobación de si es /desconocido
    if update.message.text != UNKNOWN_COMMAND and update.message.text != ACTUAL_COMMAND:
        anio = update.message.text
        if not re.match(r'^\d{4}[\/-]\d{4}$', anio):
            await update.message.reply_text("Por favor, introduce un año válido en formato 'aaaa/yyyy' o 'aaaa-yyyy', donde 'aaaa' es el año de inicio del curso y 'yyyy' el año siguiente.")
            return ANIO_EXAMEN

        context.user_data[YEAR_KEY] = update.message.text

    elif update.message.text == ACTUAL_COMMAND:
        mes = datetime.now().month
        anio = datetime.now().year

        # Si el mes es posterior a 8, entonces es anio/(anio+1). En caso contrario, es (anio-1)/anio
        if mes > 8:
            context.user_data[YEAR_KEY] = f"{anio}/{anio + 1}"
        else:
            context.user_data[YEAR_KEY] = f"{anio - 1}/{anio}"


    await update.message.reply_text(f"Por favor, indica el profesor que redactó el examen.\n(En caso de no saberlo, contestar con {UNKNOWN_COMMAND}).")
    return PROFESOR_EXAMEN


"""
Función que se encarga de la respuesta del profesor del examen.

Returns:
    int: Nuevo estado de la conversación. ES_DEPARTAMENTO_EXAMEN
"""
CALLBACK_YES = 'si'
CALLBACK_NO = 'no'
CALLBACK_UNKNOWN = 'desconocido'
async def profesor_examen_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:

    # Comprobación de si es /desconocido
    if update.message.text != UNKNOWN_COMMAND:
        context.user_data[PROFESSOR_KEY] = update.message.text
    
    # Menú para ver si el examen lo redactó el departamento
    await update.message.reply_text(
        "¿El examen lo redactó el departamento?",
        reply_markup=InlineKeyboardMarkup([
            [InlineKeyboardButton("Sí, es común para todos los grados", callback_data=CALLBACK_YES)],
            [InlineKeyboardButton("No", callback_data=CALLBACK_NO)],
            [InlineKeyboardButton("Desconocido", callback_data=CALLBACK_UNKNOWN)]
        ])
    )
    return ES_DEPARTAMENTO_EXAMEN

"""
Función que se encarga de la respuesta de si el examen lo redactó el departamento.

Returns:
    int: Nuevo estado de la conversación. GRADO_EXAMEN
"""
async def es_departamento_examen_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    query = update.callback_query
    await query.answer()
    if query.data == CALLBACK_YES:
        context.user_data[IS_DEPARTMENT_KEY] = True
    elif query.data == CALLBACK_NO:
        context.user_data[IS_DEPARTMENT_KEY] = False
        
    await query.message.reply_text(f"Por favor, indica el grado del examen (p.ej. DGIIM, Matemáticas, Informática).\n(En caso de no saberlo, contestar con {UNKNOWN_COMMAND}).")
    return GRADO_EXAMEN

"""
Función que se encarga de la respuesta del grado del examen.

Returns:
    int: Nuevo estado de la conversación. GRUPO_EXAMEN
"""
async def grado_examen_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    # Comprobación de si es /desconocido
    if update.message.text != UNKNOWN_COMMAND:
        context.user_data[GRADO_KEY] = update.message.text

    await update.message.reply_text(f"Por favor, indica el grupo del examen (A, B, etc. ó Único).\n(En caso de no saberlo, contestar con {UNKNOWN_COMMAND}).")
    return GRUPO_EXAMEN


"""
Función que se encarga de la respuesta del grupo del examen.

Returns:
    int: Nuevo estado de la conversación. FECHA_EXAMEN
"""
async def grupo_examen_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    # Comprobación de si es /desconocido
    if update.message.text != UNKNOWN_COMMAND:
        context.user_data[GROUP_KEY] = update.message.text

    await update.message.reply_text(f"Por favor, indica la fecha del examen en formato dd/mm/aaaa.\nSi es hoy, puedes contestar con {TODAY_COMMAND}.\n(En caso de no saberlo, contestar con {UNKNOWN_COMMAND}).")
    return FECHA_EXAMEN

"""
Función que se encarga de la respuesta de la fecha del examen.

Returns:
    int: Nuevo estado de la conversación. DESCRIPCION
"""
async def fecha_examen_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    # Comprobación de si es /desconocido
    if update.message.text != UNKNOWN_COMMAND and update.message.text != TODAY_COMMAND:
        
        try:

            date = datetime.strptime(update.message.text, "%d/%m/%Y")
            date_str = date.strftime("%d/%m/%Y")
            context.user_data[DATE_EX_KEY] = date_str
        except ValueError:
            await update.message.reply_text("Por favor, introduce una fecha válida en formato dd/mm/aaaa.")
            return FECHA_EXAMEN
        
    elif update.message.text == TODAY_COMMAND:
        # Si es hoy, guardamos la fecha de hoy
        date_str = get_fecha_str()
        context.user_data[DATE_EX_KEY] = date_str
    
    await update.message.reply_text(f"Por favor, describe el tipo de examen (Parcial, Convocatoria ordinaria, Extraordinaria, etc.).\n(En caso de no saberlo, contestar con {UNKNOWN_COMMAND}).")
    return DESCRIPCION

  
"""
Función que se encarga de recoger las distintas descripciones (según la opción elegida)

Returns:
    int: Nuevo estado de la conversación.
            - ARCHIVOS si se selecciona NUEVO, COMPLEMENTAR
            - CAPTURA si se selecciona CORREGIR
            - DURACION si se selecciona EXAMEN
            - MENU_OTRO si se selecciona OTRO
"""
async def descripcion_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    # Comprobación de si es /desconocido
    if update.message.text != UNKNOWN_COMMAND:
        context.user_data[DESCRIPTION_KEY] = update.message.text

    if context.user_data[OPTION_KEY] in [CALLBACK_NUEVO, CALLBACK_COMPLEMENTAR]:
        context.user_data[FILES_KEY] = []
        await update.message.reply_text(
            "Por favor, sube los archivos relacionados.\n"
            "Puedes subir tantos archivos como desees.\n"
            "Para terminar, introducir /finarchivos."
        )
        return ARCHIVOS

    elif context.user_data[OPTION_KEY] == CALLBACK_OTRO:
        await solicitar_menu_otro(update, context)
        return MENU_OTRO

    elif context.user_data[OPTION_KEY] == CALLBACK_EXAMEN:
        await update.message.reply_text(f"Por favor, indica la duración del examen en minutos.\n(En caso de no saberlo, contestar con {UNKNOWN_COMMAND}).")
        return DURACION_EXAMEN
    
"""
Función que se encarga de la respuesta de la duración del examen.

Returns:
    int: Nuevo estado de la conversación. ARCHIVOS
"""
async def duracion_examen_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    # Comprobación de si es /desconocido
    if update.message.text != UNKNOWN_COMMAND:
        try:
            duracion = int(update.message.text)
            context.user_data[DURATION_KEY] = duracion
        except ValueError:
            await update.message.reply_text("Por favor, introduce una duración válida en minutos.")
            return DURACION_EXAMEN

    context.user_data[FILES_KEY] = []
    await update.message.reply_text("Por favor, sube el archivo del examen.")
    return ARCHIVOS

"""
Función que se encarga de la respuesta del enlace del material.

Returns:
    int: Nuevo estado de la conversación.
            - DESCRIPCION si se selecciona COMPLEMENTA
            - CAPTURA si se selecciona CORREGIR
            - MENU_OTRO si se selecciona OTRO
"""
async def material_enlace_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    if update.message.text != '/noenlace':
        context.user_data[LINK_KEY] = update.message.text
        if not es_enlace(context.user_data[LINK_KEY]):
            # Si no es un enlace válido, solicitar otro y volver a este paso
            await update.message.reply_text("Por favor, proporciona un enlace válido.")
            return MATERIAL_ENLACE
    else:
        context.user_data[LINK_KEY] = None
        await update.message.reply_text(
            "No ha proporcionado un enlace, por lo que se espera que describa bien el material que va a complementar o corregir.\n"
            "De no hacerlo, no podríamos saber a qué material se refiere."
        )
    
    if context.user_data[OPTION_KEY] == CALLBACK_COMPLEMENTAR:
        await update.message.reply_text("Por favor, describe lo que se va a añadir.")
        return DESCRIPCION
    elif context.user_data[OPTION_KEY] == CALLBACK_CORREGIR:
        context.user_data[SCREENSHOT_KEY] = []
        await update.message.reply_text(
            "Por favor, sube una captura señalando el error.\n"
            "Puedes subir tantas capturas como desees. Para terminar, introduce /fincapturas.\n"
            "Tienen que ser imágenes directamente, no documentos (aunque tengan formato de imagen)."
        )
        return CAPTURA
    elif context.user_data[OPTION_KEY] == CALLBACK_OTRO:
        await solicitar_menu_otro(update, context)
        return MENU_OTRO

"""
Función que se encarga de la recepción de capturas.

Returns:
    int: Nuevo estado de la conversación. CAPTURA, ya que se pueden subir más capturas
"""
async def captura_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    if update.message.photo:

        file = await context.bot.get_file(update.message.photo[-1].file_id)
        file_name = file.file_path.strip().split('/')[-1]

        #Añade la hora al nombre del archivo
        file_name = datetime.now().strftime("%H-%M-%S_") + file_name
        
        path = os.path.join(context.user_data[DOWNLOADS_DIR_KEY], file_name)
        await file.download_to_drive(path)

        context.user_data[SCREENSHOT_KEY].append(file_name)  # Guardar nombre de la captura
        await update.message.reply_text("Captura recibida.")

        # Captura el mensaje adjunto si existe
        if update.message.caption:
            context.user_data[SCREENSHOT_KEY][-1] += " : " + update.message.caption
    
    
    
    if len(context.user_data[SCREENSHOT_KEY]) < SCREENSHOTS_LIMIT:
        await update.message.reply_text("Puedes subir más capturas o enviar /fincapturas si has terminado.")
        return CAPTURA
    
    else:
        await update.message.reply_text(f"Has alcanzado el límite de {SCREENSHOTS_LIMIT} capturas.")
        return await fincapturas_handler(update, context)

"""
Función que se encarga de la finalización de la recepción de capturas.

Returns:
    int: Nuevo estado de la conversación.
            - CORRECCION si se selecciona CORREGIR
            - MENU_OTRO si se selecciona OTRO
"""
async def fincapturas_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    
    await update.message.reply_text(
        "Recepción de capturas finalizada.\n"
        "Número de capturas recibidas: " + str(len(context.user_data[SCREENSHOT_KEY]))
    )

    if context.user_data[OPTION_KEY] == CALLBACK_OTRO:
        await solicitar_menu_otro(update, context)
        return MENU_OTRO
    else:
        await update.message.reply_text(
            "Por favor, describe la corrección que propones.\n"
            "Recuerda que, posiblemente, hayamos cursado esta asignatura hace tiempo y no recordemos bien el contenido. Detalla lo máximo posible el error."
        )
        return CORRECCION

"""
Función que se encarga de la recepción de correcciones.

Returns:
    int: Nuevo estado de la conversación.
            - CONTACTO si no tiene username
            - terminar_handler en caso contrario.
"""
async def correccion_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    context.user_data[CORRECTION_KEY] = update.message.text
    
    if not es_contactable(context.user_data):
        await update.message.reply_text("Por favor, proporciona un correo o número de teléfono de contacto (tan solo uno).\n\nTen en cuenta que se te solicitará cada vez que termines una colaboración, puesto que no dispones de username. Para evitar esto, puedes configurar un username en Telegram.")
        return CONTACTO
    else:
        return await terminar_handler(update, context)

"""
Función que se encarga de la recepción de archivos.

Returns:
    int: Nuevo estado de la conversación. ARCHIVOS, ya que se pueden subir más archivos
"""
async def archivos_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    if update.message.document or update.message.photo:

        document = update.message.document

        file_id, file_name, file = None, None, None

        try:
            if update.message.document:
                file_id = document.file_id
                file_name = document.file_name
                file = await context.bot.get_file(file_id)
            
            if update.message.photo:
                file_id = update.message.photo[-1].file_id
                file = await context.bot.get_file(file_id)
                file_name = file.file_path.strip().split('/')[-1]
        except Exception as e:
            if "File is too big" in str(e):
                await update.message.reply_text("El archivo es demasiado grande. Por favor, sube un archivo más pequeño.")
                return ARCHIVOS
            else:
                await update.message.reply_text("Ha ocurrido un error al procesar el archivo. Por favor, inténtalo de nuevo.")
                add_log(LOG_PATH, f"Error al procesar el archivo de {get_userIdentifier(context.user_data)}: {str(e)}")
                return ARCHIVOS

        #Añade la hora al nombre del archivo
        file_name = datetime.now().strftime("%H-%M-%S_") + file_name
        path = os.path.join(context.user_data[DOWNLOADS_DIR_KEY], file_name)
        await file.download_to_drive(path)

        context.user_data[FILES_KEY].append(file_name)  # Guardar nombre del archivo
        await update.message.reply_text(f"Archivo recibido: {file_name}.")

        # Captura el mensaje adjunto si existe
        if update.message.caption:
            context.user_data[FILES_KEY][-1] += " : " + update.message.caption
    

    
    if len(context.user_data[FILES_KEY]) < FILES_LIMIT:
        await update.message.reply_text("Puedes subir más archivos o enviar /finarchivos si has terminado.")
        return ARCHIVOS
    
    else:
        await update.message.reply_text(f"Has alcanzado el límite de {FILES_LIMIT} archivos.")
        return await finarchivos_handler(update, context)


"""
Función que se encarga de la finalización de recepción de archivos.

Returns:
    int: Nuevo estado de la conversación.
            - MENU_OTRO si se selecciona OTRO.
            - terminar_handler en caso contrario.

"""
async def finarchivos_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:

    await update.message.reply_text(
        'Recepción de archivos finalizada.\n'
        'Número de archivos recibidos: ' + str(len(context.user_data[FILES_KEY]))
    )

    if context.user_data[OPTION_KEY] == CALLBACK_OTRO:
        await solicitar_menu_otro(update, context)
        return MENU_OTRO
    else:
        if not es_contactable(context.user_data):
            await update.message.reply_text("Por favor, proporciona un correo o número de teléfono de contacto (tan solo uno).\n\nTen en cuenta que se te solicitará cada vez que termines una colaboración, puesto que no dispones de username. Para evitar esto, puedes configurar un username en Telegram.")
            return CONTACTO
        else:
            return await terminar_handler(update, context)

"""
Función que se encarga de la recepción del contacto.

Returns:
    int: Nuevo estado de la conversación. terminar_handler
"""
async def contacto_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    if es_email(update.message.text):
        context.user_data[EMAIL_KEY] = update.message.text
    elif es_numero_telefono(update.message.text):
        context.user_data[PHONE_KEY] = update.message.text

    # Si no se proporcionó un correo o número de teléfono válido, solicitarlo de nuevo
    if not es_contactable(context.user_data):
        await update.message.reply_text("Por favor, proporciona un correo o número de teléfono de contacto válido (tan solo uno).")
        return CONTACTO
    
    # Finalizar la conversación
    return await terminar_handler(update, context)
        

"""
Función que se encarga de finalizar la conversación.

Returns:
    int: Nuevo estado de la conversación. END
"""
async def terminar_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:

    # Guardar la hora de finalización
    context.user_data[END_TIME_KEY] = get_hora_str()

    # Avisamos de que estamos gestionando la petición
    await update.message.reply_text(
        "Procesando tu petición, por favor, espera un momento."
    )
    
    # Gestionar los datos recopilados
    if gestionar_datos(context.user_data):
        await update.message.reply_text(
            "Gracias por colaborar.\n"
            "Gestionaremos tu petición y te contactaremos si es necesario.\n"
            "Recuerda que puedes contactarnos en cualquier momento como informa en la web LosDelDGIIM.github.io/colaboracion.html.\n"
            "Si deseas colaborar en cualquier otro aspecto, por favor, escribe /start."
        )
            
        add_log(LOG_PATH, f"Petición finalizada correctamente por {get_userIdentifier(context.user_data)}.")
        os.system(f"rm -rf {context.user_data.get(DOWNLOADS_DIR_KEY)}")

    else:
        add_log(LOG_PATH, f"Error al gestionar la petición de {get_userIdentifier(context.user_data)}.")
        await update.message.reply_text(
            "Ha habido un error al gestionar tu petición. Por favor, inténtalo de nuevo y, si el problema persiste, contacta con nosotros "
            "tal y como se indica en la web LosDelDGIIM.github.io/colaboracion.html "
            "(mediante un correo directamente a losdeldgiim@gmail.com)."
        )
    

    # Limpiar los datos de la conversación
    context.user_data.clear()
    return ConversationHandler.END

"""
Función de cancelación de la conversación.

Returns:
    int: Nuevo estado de la conversación. END
"""
async def cancel(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    await update.message.reply_text(
        "La operación ha sido cancelada. Gracias de todas formas por tu tiempo.\n"
        "Si deseas colaborar en otro aspecto, por favor, escribe /start."
    )

    add_log(LOG_PATH, f"Petición cancelada por {get_userIdentifier(context.user_data)}.")

    # Elimina la carpeta creada y todo lo que haya dentro
    os.system(f"rm -rf {context.user_data.get(DOWNLOADS_DIR_KEY)}")

    # Limpiar los datos de la conversación
    context.user_data.clear()
    return ConversationHandler.END


"""
Función de ayuda del bot.
"""
async def help_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    help_text = (
        "Este bot es un asistente para colaborar con la web de LosDelDGIIM.github.io.\n"
        "Puedes colaborar con la web añadiendo material, corrigiendo errores, complementando información o aportando exámenes.\n\n"
        "Los comandos disponibles son:\n"
        "- /start - Iniciar la colaboración\n"
        "- /help - Mostrar este mensaje de ayuda\n"
        "- /cancel - Cancelar la colaboración\n"
        "- /notify - Configuración de las notificaciones\n"
        "- /finarchivos - Finalizar la subida de archivos\n"
        "- /fincapturas - Finalizar la subida de capturas\n"
        "- /noenlace - Indicar que no se proporcionará un enlace\n"
        "- /desconocido - Indicar que no se conoce la información solicitada\n"
        "- /today - Fecha actual\n\n"
        "- /cursoActual - Curso académico actual\n\n"
        "Para colaborar, tan solo tienes que seguir las instrucciones del bot.\n"
        "En el caso de detectar cualquier anomalía o bug, por favor, contacta con nosotros tal y como se indica en LosDelDGIIM.github.io/colaboracion.html.\n\n"
        "A continuación, siga por el paso en el que estaba, o bien indique /cancel para cancelar la colaboración y /start para iniciarla de nuevo.\n\n"
        "¡Gracias por colaborar con este proyecto!"
    )
    register_chat_id(CHAT_IDS_PATH, update.message.chat_id)
    await update.message.reply_text(help_text)


"""
Clase que se encarga de gestionar el envío de correos electrónicos
"""
class MailManager:
    def __init__(self):
        self.SCOPES = [
            "https://www.googleapis.com/auth/gmail.modify",
            "https://www.googleapis.com/auth/gmail.send",
            "https://www.googleapis.com/auth/gmail.labels",
            "https://www.googleapis.com/auth/gmail.compose",
            "https://www.googleapis.com/auth/gmail.settings.basic",
            "https://www.googleapis.com/auth/gmail.settings.sharing"
        ]
        self.credentials = None
        self.service = None
        self.authenticate()

    def authenticate(self):
        if os.path.exists('token.json'):
            self.credentials = Credentials.from_authorized_user_file('token.json', self.SCOPES)
        if not self.credentials or not self.credentials.valid:
            if self.credentials and self.credentials.expired and self.credentials.refresh_token:
                self.credentials.refresh(Request())
            else:
                flow = InstalledAppFlow.from_client_secrets_file('credentials.json', self.SCOPES)
                self.credentials = flow.run_local_server(port=0)
            with open('token.json', 'w') as token:
                token.write(self.credentials.to_json())

        self.service = build('gmail', 'v1', credentials=self.credentials)

    def send_mail(self, mail):
        mail.send(self.service)
        
    def save_draft(self, mail):
        mail.save_draft(self.service)

"""
Clase que se encarga de gestionar los datos recopilados y enviarlos por correo.
"""
class Mail:
    def __init__(self, to=None, subject=None, message_text=None, cc=None, bcc=None, attachments=None, html=False, userId='me'):
        self.to = to
        self.subject = subject
        self.message_text = message_text
        self.cc = cc
        self.bcc = bcc
        self.attachments = attachments
        self.html = html
        self.userId = userId
        self.messageBody = self.create_message(to, subject, message_text, cc, bcc, attachments, html)

    def create_message(self, to, subject, message_text, cc=None, bcc=None, attachments=None, html=False):
        message = MIMEMultipart()
        message['to'] = ', '.join(to) if isinstance(to, list) else to
        message['subject'] = subject

        if cc:
            message['cc'] = ', '.join(cc) if isinstance(cc, list) else cc
        if bcc:
            message['bcc'] = ', '.join(bcc) if isinstance(bcc, list) else bcc

        msg_body = MIMEText(message_text, 'html' if html else 'plain')
        message.attach(msg_body)

        if attachments:
            for file in attachments:
                self.attach_file(message, file)

        raw_message = base64.urlsafe_b64encode(message.as_bytes()).decode()
        return {'raw': raw_message}

    def attach_file(self, message, filename):
        content_type, encoding = mimetypes.guess_type(filename)
        if content_type is None or encoding is not None:
            content_type = 'application/octet-stream'

        main_type, sub_type = content_type.strip().split('/', 1)
        with open(filename, 'rb') as file:
            my_file = MIMEBase(main_type, sub_type)
            my_file.set_payload(file.read())

        encoders.encode_base64(my_file)
        my_file.add_header('Content-Disposition', f'attachment; filename="{os.path.basename(filename)}"')
        message.attach(my_file)

    def update_message_body(self):
        """Actualizar el cuerpo del mensaje después de modificar sus componentes"""
        self.messageBody = self.create_message(self.to, self.subject, self.message_text, self.cc, self.bcc, self.attachments, self.html)

    def send(self, service):
        try:
            sent_message = service.users().messages().send(userId=self.userId, body=self.messageBody).execute()
            add_log(LOG_PATH, f"Mensaje enviado exitosamente: ID {sent_message['id']}")
            return sent_message
        except HttpError as error:
            add_log(LOG_PATH, f"Ocurrió un error: {error}")
            return None

    def save_draft(self, service):
        """Guardar el mensaje como borrador"""
        try:
            draft_body = {'message': self.messageBody}  # Empaquetar el mensaje como un borrador
            draft = service.users().drafts().create(userId=self.userId, body=draft_body).execute()
            add_log(LOG_PATH, f"Borrador guardado exitosamente: ID {draft['id']}")
            return draft
        except HttpError as error:
            add_log(LOG_PATH, f"Ocurrió un error: {error}")
            return None



"""
Función que envía un correo con los datos recopilados.

Params:
    asunto (str): Asunto del correo.
    remitente (str): Nombre del remitente.
    mensaje (str): Cuerpo del correo.
    adjuntos (list): Lista con los nombres de los archivos a adjuntar.

Returns:
    True si se envió correctamente, False en caso contrario.
"""
def send_email(asunto, remitente, mensaje, adjuntos=[]) -> None:

    mail_manager = MailManager()
    
    receiver_email = "losdeldgiim@gmail.com"
    cc = None
    bcc = None
    html = True     # Indica si el mensaje es en formato HTML
    draft = False   # Indica si se va a guardar como borrador

    try:    
        mail = Mail(to=receiver_email, subject=asunto, message_text=mensaje, cc=cc, bcc=bcc, attachments=adjuntos, html=html)
        if (draft):
            mail_manager.save_draft(mail)
        else:
            mail_manager.send_mail(mail)
        return True

    
    except Exception as e:
        add_log(LOG_PATH, f"Error al enviar el correo: {e}")
        return False





"""
Función que gestiona los datos recopilados.

Devuelve true si se ha enviado correctamente, false en caso contrario.
"""
def gestionar_datos(datos: dict) -> bool:

    # Copia de los datos para no modificar los originales
    datos = datos.copy()

    # Separador para los datos
    SEPARACION = "*"*50

    # Preparamos los ajuntos a enviar, obteniendo la ruta completa de cada archivo
    adjuntos = []
    for file in datos.get(FILES_KEY, []) + datos.get(SCREENSHOT_KEY, []):
        # Quitamos la caption, si la hubiera
        file_name = file.strip().split(" : ")[0]
        adjuntos.append(os.path.join(datos.get(DOWNLOADS_DIR_KEY), file_name))
    datos.pop(DOWNLOADS_DIR_KEY)

    remitente = get_userIdentifier(datos)
    asunto = remitente + ": " + datos.get(OPTION_KEY)
    
    message_text = "<html><body>\n"
    message_text +=f"<h1>{remitente}: " + datos.pop(OPTION_KEY) + "</h1>\n"
    message_text += "<ul>\n"

    # Datos obligatorios
    message_text += f"<li>{USERNAME_KEY}: <a target=_blanck href='https://t.me/{datos.get(USERNAME_KEY)}'>{datos.pop(USERNAME_KEY)}</a></li>\n"
    for key in [NAME_KEY, LAST_NAME_KEY, PHONE_KEY, CHATID_KEY]:
        if key in datos:
            message_text += f"<li>{key}: {datos.pop(key)}</li>\n"
    if EMAIL_KEY in datos:
        message_text += f"<li>{EMAIL_KEY}: <a href='mailto:{datos.get(EMAIL_KEY)}'>{datos.pop(EMAIL_KEY)}</a></li>\n"
    for key in [INIT_TIME_KEY, END_TIME_KEY]:
        message_text += f"<li>{key}:\t{datos.pop(key)}</li>\n"

    message_text += "<li>" + SEPARACION + "</li>\n"

    # Listas (archivos y capturas)
    for key in [FILES_KEY, SCREENSHOT_KEY]:
        if key in datos and len(datos[key]) > 0:
            message_text += f"<li>{key}:\n<ul>\n"
            for file in datos.get(key):
                message_text += f"<li>{file}</li>\n"
            message_text += "</ul></li>\n"

            message_text += "<li>" + SEPARACION + "</li>\n"
        
        datos.pop(key, None)

    # Datos restantes
    if LINK_KEY in datos:
        message_text += f"<li>{LINK_KEY}: <a target=_blanck href={datos.get(LINK_KEY)}>{datos.pop(LINK_KEY)}</a></li>\n"

    # En el feature de escaneo de exámenes se hace uso de estas variables para solicitarle la información sobre el examen al usuario
    # Como no queremos que su contenido sea enviado por correo las limpiamos aquí
    datos.pop('FOTOS_IA',None)
    datos.pop('codigo_latex',None)

    for key, value in datos.items():
        message_text += f"<li>{key}: {value}</li>\n"

    message_text += "</ul>\n"
    message_text += "</body></html>"

    return send_email(asunto, remitente, message_text, adjuntos)
    

# Aquí se inserta la API key de Google AI Studio pero la pilla automáticamente del .env
client = genai.Client()

"""
Función que acumula las imágenes que le manda el usuario al bot para hacer una transcripción de examen

Acumula los nombres de todas en la variable 'FOTOS_IA' de context.user_data y las descarga en el directorio de usuario
"""
async def acumular_fotos_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    if update.message.photo:
        file = await context.bot.get_file(update.message.photo[-1].file_id)

        directorio_usuario = context.user_data.get(DOWNLOADS_DIR_KEY, DOWNLOAD_BASEDIR)

        if 'FOTOS_IA' not in context.user_data:
            context.user_data['FOTOS_IA'] = []
        
        # Le damos un nombre único a cada foto basándonos en cuántas hay ya guardadas
        numero_foto = len(context.user_data.get('FOTOS_IA', [])) + 1
        file_name = f"temp_examen_{numero_foto}.jpg"
        file_path = os.path.join(directorio_usuario, file_name)
        await file.download_to_drive(file_path)
        
        # Guardamos la ruta en la lista
        context.user_data['FOTOS_IA'].append(file_name)
        
        await update.message.reply_text(f"Página {numero_foto} guardada. Sube la siguiente o escribe /finarchivos.")
    else:
        await update.message.reply_text("Solo se aceptan imágenes del examen, este archivo ha sido ignorado. Por favor manda una imagen")
    return ESCANEO

"""
Función auxiliar que rescata los distintos archivos cuyo contenido está presente en el prompt para la IA
y luego los inyecta en un único string
"""
def construir_instrucciones_ia() -> str:
    # Importante tener bien la ruta del prompt, pues partimos del DOWNLOAD_BASEDIR que es distinto en el server
    with open(PLANTILLA_PATH, "r", encoding="utf-8") as f:
        texto_plantilla = f.read()
    with open(PREAMBULO_PATH, "r", encoding="utf-8") as f:
        texto_preambulo_completo = f.read()
        partes = texto_preambulo_completo.split("% IA")
        if len(partes) > 1:
            texto_preambulo = partes[1].strip()
        else:
            texto_preambulo = "No hay macros concretas definidas."
            add_log(LOG_PATH, "Advertencia: No se encontraron macros definidas para IA en preambulo.tex, para añadirlas hay que escribir % IA y todo lo que venga detrás serán macros para la IA")
    with open(PROMPT_PATH, "r", encoding="utf-8") as f:
        plantilla_prompt = f.read()

    return plantilla_prompt.format(
        texto_plantilla = texto_plantilla,
        texto_preambulo = texto_preambulo
    )


"""
Funcion que se encarga de manejar el flujo para hacer la transcripcion del examen a LaTeX

Espera que el usuario haya mandado una serie de imagenes del examen, carga el prompt del archivo prompt_ocr.txt en el que le inyecta
la plantilla de examen y el preambulo.

Hace una llamada a la API de gemini de google AI studio y recibe el código LaTeX que transcribe el examen

Por si acaso Gemini halucina, habla más de la cuenta o escribe algo que no sea LaTeX en el paso 4 se realiza un filtro para extraer solo un bloque de código LaTeX

En caso de faltar información sobre el examen se lleva la conversación a un nuevo estado en el que entra en juego el manejador recuperar_metadatos_handler

Una vez gestionado eso se prepara el correo y se envia el código LaTeX al usuario y por correo
"""
async def procesar_examen_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    # Nombres de los archivos
    fotos = context.user_data.get('FOTOS_IA', [])
    directorio_usuario = context.user_data.get(DOWNLOADS_DIR_KEY, DOWNLOAD_BASEDIR)
    
    if not fotos:
        await update.message.reply_text("No has subido ninguna foto. Sube alguna o escribe /cancel.")
        return ESCANEO

    await update.message.reply_text(f"Procesando {len(fotos)} páginas con la IA y aplicando la plantilla... Esto tardará un poco.")

    
    # 1. Plantilla y preámbulo obtenidos del repo
    try:
        instrucciones_sistema = construir_instrucciones_ia()
    except Exception as e:
        os.system(f"rm -rf {context.user_data.get(DOWNLOADS_DIR_KEY)}")
        raise
    
    # 2. Añadimos las fotos
    contenidos = []
    for foto in fotos:
        ruta_completa = os.path.join(directorio_usuario,foto)
        with open(ruta_completa, "rb") as f:
            contenidos.append(types.Part.from_bytes(data=f.read(), mime_type='image/jpeg'))
            
    # Añadimos la orden de texto al final de las fotos
    # Con esto terminamos el prompt normal, el que se le escribe
    contenidos.append("Transcribe todo este examen en orden, respetando la plantilla.")

    # 3. Llamada a la IA, a veces lanza un 503, por tanto probamos unos cuantos intentos
    MAX_INTENTOS = 3
    response = None

    for intento in range(MAX_INTENTOS):
        try:
            response = client.models.generate_content(
                model='gemini-3.5-flash',
                contents=contenidos,
                config=types.GenerateContentConfig(
                    system_instruction=instrucciones_sistema,
                    # Este factor es importante mantenerlo en 0
                    # Parecido al enfriamiento simulado, el algoritmo de la IA para generar palabras tiene una temperatura
                    # que a mayor valor aplana más la distribución de probabilidad en la que se basa para elegir palabras
                    # resultando en respuestas aleatorias, impredecibles y para nada relacionadas con lo que queremos.
                    temperature=0.0
                )
            )
            break # Si funciona, salimos del bucle inmediatamente

        except Exception as e:
            error_str = str(e)
            if "503" in error_str or "UNAVAILABLE" in error_str:
                # Comprobamos si NO es el último intento (recuerda que empiezan en 0)
                if intento < MAX_INTENTOS - 1:
                    await update.message.reply_text(f"Los servidores se encuentran saturados. Se hará un reintento automático en 30 segundos... (Intento {intento+1}/{MAX_INTENTOS})")
                    await asyncio.sleep(30)
                else:
                    # Es el último intento, avisamos y ABORTAMOS
                    await update.message.reply_text("Los servidores están demasiado saturados en este momento. Por favor, inténtalo más tarde.")
                    add_log(LOG_PATH,"Se agotaron los intentos por error 503.")
                    
                    return await cancel(update,context)
            else:
                # Si es un error grave distinto a 503, también abortamos
                
                os.system(f"rm -rf {context.user_data.get(DOWNLOADS_DIR_KEY)}")
                raise
 
    # 4. Filtrado
    # Si el código ha llegado hasta esta línea, es matemáticamente seguro que 'response' 
    # tiene la respuesta de la IA (si no, el 'return' del bloque anterior nos habría sacado de la función).
    match = re.search(r'(\\documentclass.*?\\end\{document\})', response.text, re.DOTALL)
    
    if match:
        codigo_limpio = match.group(1)

        metadatos_faltantes = re.findall(r'%\s*\\item\[(.*?)\]', codigo_limpio)

        if not metadatos_faltantes:
            tex_filename = "Examen_TranscritoIA.tex"
            tex_path = os.path.join(directorio_usuario, tex_filename)
            with open(tex_path, "w", encoding="utf-8") as f:
                f.write(codigo_limpio)
            
            await update.message.reply_document(
                document=open(tex_path, 'rb'), 
                caption="¡Examen completo procesado! Aun así te animamos resolverlo y que nos lo envíes para poder subirlo resuelto."
            )

            # 5. Enviar correo, en este caso ya tenemos todos los metadatos asegurados
            context.user_data[OPTION_KEY] = 'Transcripción IA Examen'
            context.user_data[DESCRIPTION_KEY] = 'Examen transcrito automáticamente con Gemini 3.5 Flash. Se adjuntan escaneos originales y código LaTeX.'

            context.user_data[FILES_KEY] = fotos + [tex_filename]
                    
            return await terminar_handler(update,context)
        else:
            context.user_data['codigo_latex'] = codigo_limpio

            mensaje_instrucciones = (
                "¡Examen procesado por la IA!\n\n"
                "Sin embargo, no he podido leer algunos datos del encabezado de la imagen. "
                "Por favor, **copia el siguiente mensaje**, rellena los huecos y envíamelo de vuelta "
                "(o escribe /omitir si prefieres dejarlo vacío):"
            )

            mensaje_plantilla = ""

            for metadato in metadatos_faltantes:
                mensaje_plantilla += f"{metadato}: \n"

            await update.message.reply_text(mensaje_instrucciones,parse_mode= 'Markdown')
            await update.message.reply_text(mensaje_plantilla)
            return RECUPERAR_METADATOS

    else:
        await update.message.reply_text("La IA no ha podido generar una estructura LaTeX válida con estas fotos. Inténtalo con imágenes más claras.")
        return await cancel(update, context)

async def recuperar_metadatos_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    respuesta_usuario = update.message.text
    codigo_actualizado = context.user_data['codigo_latex']

    # Si el usuario no ha escrito /omitir, habrá algún campo relleno
    if respuesta_usuario != '/omitir':
        lineas = respuesta_usuario.split('\n')

        for linea in lineas:
            if ':' in linea:
                partes = linea.split(':',1)
                clave = partes[0].strip()
                valor = partes[1].strip()

                # Si el usuario ha rellenado el campo
                if valor:
                    # Buscamos el item identificado por clave y lo rellenamos con valor
                    patron = re.compile(r'%\s*\\item\[' + re.escape(clave) + r'\].*')

                    # Al parecer si no usamos una función lambda aquí, el paquete re busca caracteres de escape como \1,\2 y al encontrar \i en \item peta
                    codigo_actualizado = patron.sub(
                        lambda m, cl=clave, vl=valor: f"\\item[{cl}] {vl}", 
                        codigo_actualizado
                    )

                    context.user_data[f"Metadato aportado por el usuario ({clave})"] = valor
    
    directorio_usuario = context.user_data.get(DOWNLOADS_DIR_KEY, DOWNLOAD_BASEDIR)
    tex_filename = "Examen_TranscritoIA.tex"
    tex_path = os.path.join(directorio_usuario, tex_filename)

    with open(tex_path, "w", encoding="utf-8") as f:
        f.write(codigo_actualizado)
    
    await update.message.reply_document(
        document=open(tex_path, 'rb'), 
        caption="¡Examen completo procesado! Aun así te animamos resolverlo y que nos lo envíes para poder subirlo resuelto."
    )

    # 5. Enviar correo, en este caso ya tenemos todos los metadatos asegurados
    context.user_data[OPTION_KEY] = 'Transcripción IA Examen'
    context.user_data[DESCRIPTION_KEY] = 'Examen transcrito automáticamente con Gemini 3.5 Flash. Se adjuntan escaneos originales y código LaTeX.'

    context.user_data[FILES_KEY] = context.user_data.get('FOTOS_IA', []) + [tex_filename]
            
    return await terminar_handler(update,context)

"""
Copia de funcion start pero que lleva directamente al estado de escaneo

Funcion creada para el testeo del feature de escaneo de exámenes para estar oculta del menú público del bot y ser solo accesible
a aquellos que conozcan el comando
"""
async def comando_IA(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    if has_exceeded_requests(context):
        add_log(LOG_PATH, f"El usuario {get_userIdentifier(context.user_data)} ha excedido el límite de peticiones (IA).")
        await update.message.reply_text(
            f"Has excedido el límite de {REQUESTS_LIMIT} peticiones en {TIME_LIMIT} segundos. Por favor, inténtalo de nuevo más tarde."
        )
        context.user_data.clear()
        return ConversationHandler.END
    
    add_log(LOG_PATH, f"Peticion secreta de IA iniciada por {get_userIdentifier(context.user_data)}.")

    file_name = context.user_data[INIT_TIME_KEY] + "_" + get_userIdentifier(context.user_data)
    context.user_data[DOWNLOADS_DIR_KEY] = os.path.join(DOWNLOAD_BASEDIR, file_name)
    os.makedirs(context.user_data[DOWNLOADS_DIR_KEY])

    context.user_data[OPTION_KEY] = CALLBACK_ESCANEO
    context.user_data['FOTOS_IA'] = []

    # Se llama a la función para actualizar las plantillas cada vez que se hace una petición
    try:
        actualizar_plantillas_desde_github()
    except Exception as e:
        # Error critico, sin plantillas no podemos transcribir el examen
        os.system(f"rm -rf {context.user_data.get(DOWNLOADS_DIR_KEY)}")
        raise
    
    await update.message.reply_text(
        "Has elegido escanear un examen con IA.\n\n"
        "Sube fotos claras del examen que quieres pasar a código LaTeX.\n"
        "Recuerda enviar /finarchivos al terminar.",
        parse_mode='Markdown'
    )
    return ESCANEO


"""
Función que se encarga de manejar los mensajes desconocidos.
"""
async def unknown_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    msg = "Lo siento, no he entendido tu mensaje. Puedes pulsar /cancel para cancelar la operación y volver a empezar."
    if update.message:
        await update.message.reply_text(msg)
    elif update.callback_query:
        await update.callback_query.answer()
        await update.callback_query.message.reply_text(msg)

"""
Función que se encarga de manejar los mensajes antes de iniciar la conversación.
"""
async def unstarted_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    register_chat_id(CHAT_IDS_PATH, update.message.chat_id)
    msg = "Lo siento, no he entendido tu mensaje.\nAún no has iniciado una colaboración. Por favor, pulsa /start para iniciar una colaboración.\nTambién puedes emplear algunos comandos de gestión, como /notify."
    await update.message.reply_text(msg)

"""
    Envía un mensaje a todos los chat_ids registrados en el archivo chat_ids_path que tengan configurado la notificación
"""
async def notificar(chat_ids_path: str, message: str) -> None:
    message = "<b>Aviso de LosDelDGIIM</b>:\n\n" + message + "\n\nSi no desea recibir estos avisos, pulsar /notify."


    chat_ids = []
    for line in open(chat_ids_path, 'r'):
        if line.strip().split(SEPARATOR)[1] == 'True':  # Solo notificar a los que tienen la notificación activada
            chat_ids.append(line.strip().split(SEPARATOR)[0])
    
    if not chat_ids:
        add_log(LOG_PATH, "No hay usuarios registrados para enviar la notificación.")
        return False
    
    hayError = False
    for chat_id in chat_ids:
        try:
            bot = Bot(token=TOKEN)
            await bot.send_message(chat_id=chat_id, text=message, parse_mode="HTML")
        except Forbidden as e:
            # El usuario ha bloqueado el bot, no es un error crítico
            add_log(LOG_PATH, f"Usuario {chat_id} ha bloqueado el bot - omitiendo notificación")
        except Exception as e:
            add_log(LOG_PATH, f"Error al enviar la notificación a {chat_id}: {e}")
            hayError = True

            #Notificar al admin del error
            try:
                await bot.send_message(chat_id=ADMINS_IDS[0], text=f"Error al enviar la notificación a {chat_id}: {e}")
            except:
                pass
    
    if (not hayError):
        add_log(LOG_PATH, "Notificación enviada correctamente a todos los usuarios registrados.")
    
    return not hayError


async def send_notification(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    context.user_data[USERNAME_KEY] = update.message.from_user.username
    context.user_data[NAME_KEY] = update.message.from_user.first_name
    context.user_data[LAST_NAME_KEY] = update.message.from_user.last_name
    context.user_data[INIT_TIME_KEY] = get_hora_str()
    context.user_data[CHATID_KEY] = update.message.chat_id

    register_chat_id(CHAT_IDS_PATH, update.message.chat_id)
    add_log(LOG_PATH, f"Usuario {get_userIdentifier(context.user_data)} ha solicitado enviar una notificación.")

    if context.user_data.get(CHATID_KEY) in ADMINS_IDS:
        await update.message.reply_text("Mensaje a enviar:")
        return NOTIFICACION
    else:
        msg = "Lo siento, no he entendido tu mensaje. Puedes pulsar /cancel para cancelar la operación y volver a empezar."
        await update.message.reply_text(msg)
        context.user_data.clear()
        return ConversationHandler.END

    """Anterior implementación, con contraseña
    await update.message.reply_text("Contraseña:")
    return PASSWD
    """

async def passwd_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    passwd = update.message.text
    if passwd != NOTIFICATION_PASSWORD:
        await update.message.reply_text("Contraseña incorrecta. Por favor, inténtalo de nuevo.\nSi no tienes contraseña, pulsa /cancel.")
        return PASSWD
    
    await update.message.reply_text("Mensaje a enviar:")
    return NOTIFICACION

async def notification_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    message = update.message.text
    if not message:
        await update.message.reply_text("El mensaje no puede estar vacío. Por favor, inténtalo de nuevo.")
        return NOTIFICACION
    
    # Enviar el mensaje a todos los chat_ids registrados
    if (await notificar(CHAT_IDS_PATH, message)):
        await update.message.reply_text("Notificación enviada a todos los usuarios registrados.")
    else:
        await update.message.reply_text("Error al enviar la notificación. Por favor, inténtalo de nuevo más tarde.")
    
    context.user_data.clear()  # Limpiar los datos de la conversación
    return ConversationHandler.END


async def ask_notification_conf(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    context.user_data[CHATID_KEY] = update.message.chat_id
    register_chat_id(CHAT_IDS_PATH, update.message.chat_id)
    add_log(LOG_PATH, f"Usuario {get_userIdentifier(context.user_data)} ha solicitado configurar las notificaciones.")
    conf_anterior = True
    for line in open(CHAT_IDS_PATH, 'r'):
        if line.strip().split(SEPARATOR)[0] == str(update.message.chat_id):
            conf_anterior = line.strip().split(SEPARATOR)[1] == 'True'
            break

    msg = "Aquí puedes configurar las notificaciones del bot.\n"
    if conf_anterior:
        msg += "Actualmente tienes las notificaciones <b>activadas</b>.\n\n"
        msg += "🔘 Notifícame de los cambios más relevantes.\n\n"
        msg += "⚫️ No quiero que me notifiques."
    else:
        msg += "Actualmente tienes las notificaciones <b>desactivadas</b>.\n\n"
        msg += "⚫️ Notifícame de los cambios más relevantes.\n\n"
        msg += "🔘 No quiero que me notifiques."


    await update.message.reply_text(msg,
        parse_mode="HTML",
        reply_markup=InlineKeyboardMarkup([
            [InlineKeyboardButton("SÍ quiero que me avises", callback_data=CALLBACK_NOTIFICAR)],
            [InlineKeyboardButton("NO quiero que me avises", callback_data=CALLBACK_NO_NOTIFICAR)]
        ])
    )
    return NOTIFICACION_PROCESAR

async def notification_conf_handler(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    await update.callback_query.answer()
    nueva_conf = update.callback_query.data == CALLBACK_NOTIFICAR

    tmp = "activado" if nueva_conf else "desactivado"

    add_log(LOG_PATH, f"Usuario {get_userIdentifier(context.user_data)} ha {tmp} las notificaciones.")
    
    with open(CHAT_IDS_PATH, 'r') as f:
        lines = f.readlines()
    
    with open(CHAT_IDS_PATH, 'w') as f:
        for line in lines:
            if line.strip().split(SEPARATOR)[0] == str(update.callback_query.message.chat_id):
                f.write(f"{update.callback_query.message.chat_id}{SEPARATOR}{nueva_conf}\n")
            else:
                f.write(line)
    
    
    tmp = "activadas" if nueva_conf else "desactivadas"
    await update.callback_query.message.reply_text(f"Notificaciones {tmp} correctamente.")
    context.user_data.clear()  # Limpiar los datos de la conversación
    return ConversationHandler.END


"""
Función que se encarga de manejar los errores del bot.
"""
async def error_handler(update: object, context: ContextTypes.DEFAULT_TYPE):
    try:
        user_identifier = (
            get_userIdentifier(context.user_data)
            if context.user_data
            else "desconocido"
        )
    except Exception:
        user_identifier = "desconocido"

    error = context.error

    # --- Traceback completo ---
    tb = "".join(
        traceback.format_exception(None, error, error.__traceback__)
    ) if error else "No traceback disponible"

    # --------------------------------------------------
    # 🚦 CLASIFICACIÓN DE ERRORES
    # --------------------------------------------------

    # ❌ Errores de red / Telegram (no notificar usuarios ni admins)
    if isinstance(error, (NetworkError, TimedOut, Conflict)):
        add_log(LOG_PATH, f"Error de red/Telegram ignorado: {type(error).__name__}")
        return

    # ❌ Errores HTTPX (red)
    if "httpx" in type(error).__module__:
        add_log(LOG_PATH, "Error httpx detectado (red o respuesta incompleta)")
        return

    # --- Log principal ---
    add_log(
        LOG_PATH,
        f"Error en el bot con el usuario {user_identifier}: {error}\n{tb}"
    )

    # --------------------------------------------------
    # 👤 NOTIFICAR AL USUARIO (solo si procede)
    # --------------------------------------------------
    if isinstance(update, Update) and update.effective_user:
        try:
            await update.effective_user.send_message(
                "⚠️ Ocurrió un error interno al procesar tu solicitud.\n"
                "Intenta nuevamente más tarde.\n"
                "Si el problema persiste, contacta con los administradores."
            )
        except Exception:
            # Nunca relanzar desde el error handler
            pass

    # --------------------------------------------------
    # 🚨 NOTIFICAR A ADMINS (con rate-limit básico)
    # --------------------------------------------------
    admin_msg = (
        "🚨 *ALERTA BOT*\n\n"
        f"👤 Usuario: `{user_identifier}`\n"
        f"❌ Error: `{error}`\n\n"
        f"📄 Traceback:\n```{tb[-3500:]}```"
    )

    for admin_id in ADMINS_IDS:
        try:
            await context.bot.send_message(
                chat_id=admin_id,
                text=admin_msg,
                parse_mode="Markdown"
            )
            await asyncio.sleep(0.2)  # evita flood
        except Exception:
            pass


def actualizar_plantillas_desde_github():
    """
    Descarga la última versión del preámbulo y la plantilla directamente 
    desde GitHub al arrancar el bot y los guarda localmente.
    """
    # URLs crudas de los archivos en el repo
    url_base = "https://raw.githubusercontent.com/LosDelDGIIM/LosDelDGIIM.github.io/main/subjects"
    
    archivos = {
        "Plantilla_Ex.tex": f"{url_base}/plantillas/Exámenes/Plantilla_Ex.tex",
        "preambulo.tex": f"{url_base}/_assets/preambulo.tex"
    }
    
    # Crear el directorio para las plantillas
    os.makedirs(PLANTILLAS_BASEDIR, exist_ok=True)
    
    for nombre, url in archivos.items():
        respuesta = httpx.get(url, timeout=10.0)
        respuesta.raise_for_status() # Asegura que la descarga fue exitosa (HTTP 200)
        
        ruta_local = os.path.join(PLANTILLAS_BASEDIR, nombre)
        with open(ruta_local, "w", encoding="utf-8") as f:
            f.write(respuesta.text)


"""
Función principal que inicia el bot.

No devuelve nada, tan solo inicia el bot.
"""
def main() -> None:
    application = Application.builder().token(TOKEN).build()

    conv_handler = ConversationHandler(
        entry_points=[CommandHandler('start', start), CommandHandler('escaneo',comando_IA)],
        states={
            MENU:
                [CallbackQueryHandler(menu_handler)],
            MENU_OTRO:
                [CallbackQueryHandler(menu_otro_handler)],
            CURSO:
                [CallbackQueryHandler(curso_handler)],
            ASIGNATURA:
                [CallbackQueryHandler(asignatura_handler)],
            DESCRIPCION:
                [MessageHandler(filters.TEXT & ~filters.COMMAND, descripcion_handler),
                 CommandHandler('desconocido', descripcion_handler)],
            MATERIAL_ENLACE:
                [MessageHandler(filters.TEXT & ~filters.COMMAND, material_enlace_handler),
                 CommandHandler('NoEnlace', material_enlace_handler)],
            CAPTURA:
                [MessageHandler(filters.PHOTO, captura_handler),
                 CommandHandler('fincapturas', fincapturas_handler)],
            CORRECCION:
                [MessageHandler(filters.TEXT & ~filters.COMMAND, correccion_handler)],
            ARCHIVOS:
                [MessageHandler(filters.Document.ALL | filters.PHOTO, archivos_handler),
                 CommandHandler('finarchivos', finarchivos_handler)],
            CONTACTO:
                [MessageHandler(filters.TEXT & ~filters.COMMAND, contacto_handler)],
            ANIO_EXAMEN: 
                [MessageHandler(filters.TEXT & ~filters.COMMAND, anio_examen_handler),
                 CommandHandler('desconocido', anio_examen_handler),
                 CommandHandler('cursoActual', anio_examen_handler)],
            PROFESOR_EXAMEN:
                [MessageHandler(filters.TEXT & ~filters.COMMAND, profesor_examen_handler),
                 CommandHandler('desconocido', profesor_examen_handler)],
            ES_DEPARTAMENTO_EXAMEN:
                [CallbackQueryHandler(es_departamento_examen_handler)],
            GRADO_EXAMEN:
                [MessageHandler(filters.TEXT & ~filters.COMMAND, grado_examen_handler),
                 CommandHandler('desconocido', grado_examen_handler)],
            GRUPO_EXAMEN:
                [MessageHandler(filters.TEXT & ~filters.COMMAND, grupo_examen_handler),
                 CommandHandler('desconocido', grupo_examen_handler)],
            FECHA_EXAMEN:
                [MessageHandler(filters.TEXT & ~filters.COMMAND, fecha_examen_handler),
                 CommandHandler('desconocido', fecha_examen_handler),
                 CommandHandler('today', fecha_examen_handler)],
            DURACION_EXAMEN:
                [MessageHandler(filters.TEXT & ~filters.COMMAND, duracion_examen_handler),
                 CommandHandler('desconocido', duracion_examen_handler)],
            FORMA_AYUDA:
                [MessageHandler(filters.TEXT & ~filters.COMMAND, forma_ayuda_handler)],
            ESCANEO:
                [MessageHandler(filters.ALL & ~filters.COMMAND, acumular_fotos_handler),
                 CommandHandler('finarchivos', procesar_examen_handler)],
            RECUPERAR_METADATOS:
                [MessageHandler(filters.TEXT & ~filters.COMMAND, recuperar_metadatos_handler),
                 CommandHandler('omitir',recuperar_metadatos_handler)],
            PETICION_ASIGNATURA:
                [MessageHandler(filters.TEXT & ~filters.COMMAND, peticion_asignatura_handler)],
        },
        fallbacks=[
            CommandHandler('cancel', cancel),
            MessageHandler(filters.ALL, unknown_handler),
            CallbackQueryHandler(unknown_handler)          # <-- Para callbacks inesperados
        ]
    )


    conv_notification_handler = ConversationHandler(
        entry_points=[CommandHandler('enviarAviso', send_notification)],
        states={
            PASSWD:
                [MessageHandler(filters.TEXT & ~filters.COMMAND, passwd_handler)],
            NOTIFICACION:
                [MessageHandler(filters.TEXT & ~filters.COMMAND, notification_handler)]
        },
        fallbacks=[
            CommandHandler('cancel', cancel),
            MessageHandler(filters.ALL, unknown_handler),
            CallbackQueryHandler(unknown_handler)          # <-- Para callbacks inesperados
        ]
    )


    conv_conf_notification_handler = ConversationHandler(
        entry_points=[CommandHandler('notify', ask_notification_conf)],
        states={
            NOTIFICACION_PROCESAR:
                [CallbackQueryHandler(notification_conf_handler)]
        },
        fallbacks=[
            CommandHandler('cancel', cancel),
            MessageHandler(filters.ALL, unknown_handler),
            CallbackQueryHandler(unknown_handler)          # <-- Para callbacks inesperados
        ]
    )

    # Añadimos el handler a la aplicación
    application.add_handler(conv_handler)
    application.add_handler(conv_notification_handler)
    application.add_handler(conv_conf_notification_handler)

    # Añadimos el handler de /help fuera del ConversationHandler
    application.add_handler(CommandHandler('help', help_handler))
    application.add_handler(MessageHandler(filters.ALL, unstarted_handler))  # Para mensajes inesperados antes de iniciar la conversación

    # Handler de errores
    application.add_error_handler(error_handler)


    # Crear directorio de descargas si no existe, para guardar los archivos
    os.makedirs(DOWNLOAD_BASEDIR, exist_ok=True)

    # Verificar si el archivo de LOG ya existe
    if os.path.exists(LOG_PATH):
        # Renombrar el archivo existente a un nombre que no exista
        log_file_path = LOG_PATH
        i = 1
        while os.path.exists(log_file_path):
            log_file_path = f"{LOG_PATH}_{i}"
            i += 1
        
        # Renombrar el archivo
        os.rename(LOG_PATH, log_file_path)

    # Verificar si el archivo de CHAT_IDS ya existe
    if not os.path.exists(CHAT_IDS_PATH):
        # Crear el archivo de CHAT_ID si no existe
        with open(CHAT_IDS_PATH, 'w') as f:
            f.write("")

    msg_init = "-"*50 + "\n"
    msg_init += f"Bot iniciado a las {get_hora_str()}.\n"
    msg_init += "-"*50 + "\n"
    # Crear el nuevo archivo y escribir el mensaje de inicio
    with open(LOG_PATH, 'w') as f:
        f.write(msg_init)

    # Mostrar el mensaje de inicio en la consola
    print(msg_init)
    print("Pulsar Ctrl+C para detener el bot.\n\n")

        
    # Inicia el bot
    application.run_polling()


if __name__ == '__main__':
    main()