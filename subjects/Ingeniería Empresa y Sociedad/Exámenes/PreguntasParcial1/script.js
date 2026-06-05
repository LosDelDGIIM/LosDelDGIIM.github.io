const preguntas = [
  {
    enunciado: "¿Qué es una organización según la definición vista en el tema 1?",
    opciones: [
      "Una unidad económica que solo busca beneficios",
      "Un conjunto de máquinas y recursos financieros",
      "Una sociedad mercantil inscrita en el registro",
      "Una unidad coordinada formada por un mínimo de dos personas que trabajan para alcanzar objetivos comunes"
    ],
    correcta: 3,
    explicacion: "Diapositiva 4 del tema 1."
  },
  {
    enunciado: "¿Cuál de las siguientes definiciones vistas de empresa es la de Barroso, 2010?",
    opciones: [
      "Una unidad técnico-económica que transforma un conjunto de recursos según una tecnología dada en productos o servicios, generando en ese proceso valor añadido.",
      "Un conjunto ordenado de factores productivos orientados al desarrollo de una función específica, bajo la dirección y control del empresario.",
      "Una unidad técnico-económica que transforma un conjunto de recursos según una tecnología dada en bienes materiales, generando en ese proceso beneficio inmediato.",
      "Unidad económica que combina un conjunto de elementos humanos, técnicos y financieros, ordenados según determinada estructura de organización y dirigidos en base a cierta relación de propiedad y control."
    ],
    correcta: 0,
    explicacion: "Diapositiva 6 del tema 1. La correcta es la primera. La segunda opción corresponde a Alegre, Berné y Galve, 1995; la cuarta está tomada de Bueno Campos et al., 2002; y la tercera no coincide exactamente con la de Barroso."
  },
  {
    enunciado: "Una empresa es:",
    opciones: [
      "Una organización que transforma recursos en bienes o servicios y busca beneficio",
      "Cualquier grupo de personas",
      "Cualquier institución pública",
      "Una asociación sin objetivos económicos"
    ],
    correcta: 0,
    explicacion: "Diapositiva 8 del tema 1."
  },
  {
    enunciado: "Señala la afirmación correcta: (Según el profesor, una de las preguntas que dice que pone: diferencia entre empresa y organización (diapositiva 9 del tema 1))",
    opciones: [
      "Toda organización es una empresa",
      "Empresa y organización son exactamente lo mismo",
      "Ninguna empresa es una organización",
      "Toda empresa es una organización"
    ],
    correcta: 3,
    explicacion: "Diapositiva 8 del tema 1."
  },
  {
    enunciado: "Según la postura de Friedman, la empresa debe:",
    opciones: [
      "Maximizar el beneficio respetando las leyes y evitando engaños y fraudes",
      "Satisfacer exclusivamente a los empleados",
      "Renunciar al beneficio en favor del interés general",
      "Subordinar todas sus decisiones a la administración pública"
    ],
    correcta: 0,
    explicacion: "Diapositiva 11 del tema 1."
  },
  {
    enunciado: "Según Freeman, la empresa debe:",
    opciones: [
      "Buscar solo la rentabilidad financiera de los propietarios",
      "Satisfacer no solo a los propietarios, sino también al resto de stakeholders",
      "Eliminar la dirección profesional",
      "Centrarse únicamente en el corto plazo"
    ],
    correcta: 1,
    explicacion: "Diapositiva 11 del tema 1."
  },
  {
    enunciado: "Atendiendo a su forma jurídica, ¿cuál de las siguientes es una forma societaria?",
    opciones: [
      "Sociedad de responsabilidad limitada",
      "Sociedad de liquidez inmediata",
      "Sociedad de equilibrio patrimonial",
      "Sociedad de coste marginal"
    ],
    correcta: 0,
    explicacion: "Diapositiva 13 del tema 1."
  },
  {
    enunciado: "Una empresa mediana se caracteriza, entre otros criterios, por tener:",
    opciones: [
      "Menos de 10 trabajadores",
      "Más de 250 trabajadores",
      "Menos de 250 trabajadores",
      "Exactamente 50 trabajadores"
    ],
    correcta: 2,
    explicacion: "Diapositiva 14 del tema 1."
  },
  {
    enunciado: "Según el criterio de tamaño, una empresa pequeña tiene:",
    opciones: [
      "Menos de 50 trabajadores",
      "Menos de 250 trabajadores",
      "Menos de 10 trabajadores",
      "Más de 50 millones de euros de cifra de negocios"
    ],
    correcta: 0,
    explicacion: "Diapositiva 14 del tema 1."
  },
  {
    enunciado: "Una microempresa se caracteriza, principalmente, por tener:",
    opciones: [
      "Menos de 250 trabajadores",
      "Menos de 50 trabajadores",
      "Menos de 10 trabajadores",
      "Menos de 5 trabajadores"
    ],
    correcta: 2,
    explicacion: "Diapositiva 14 del tema 1."
  },
  {
    enunciado: "Según el enfoque sistémico, un sistema se caracteriza por:",
    opciones: [
      "Operar solo con entradas",
      "Operar con entradas y proveer salidas procesadas",
      "Funcionar únicamente con objetivos y normas",
      "Depender solo de información financiera"
    ],
    correcta: 1,
    explicacion: "Diapositiva 18 del tema 1."
  },
  {
    enunciado: "Según el enfoque sistémico, la empresa es un sistema abierto porque:",
    opciones: [
      "No necesita control interno",
      "Solo intercambia información",
      "Está en constante interacción con su entorno, influye en él y es influida por él",
      "Carece de objetivos definidos"
    ],
    correcta: 2,
    explicacion: "Diapositiva 19 del tema 1."
  },
  {
    enunciado: "El mecanismo por el que la empresa corrige desviaciones respecto a sus objetivos se llama:",
    opciones: [
      "Feedback o retroalimentación",
      "Outsourcing",
      "Sinergia",
      "Inversión"
    ],
    correcta: 0,
    explicacion: "Diapositiva 22 del tema 1."
  },
  {
    enunciado: "La homeostasis de la empresa hace referencia a:",
    opciones: [
      "La capacidad de vender existencias a corto plazo",
      "El equilibrio interno obtenido tras la autorregulación",
      "La rentabilidad mínima exigida por los accionistas",
      "La dependencia de proveedores"
    ],
    correcta: 1,
    explicacion: "Diapositiva 22 del tema 1."
  },
  {
    enunciado: "El principio de jerarquía de los sistemas permite:",
    opciones: [
      "Eliminar los subsistemas funcionales",
      "Descomponer el sistema en partes o subsistemas",
      "Sustituir la empresa por el mercado",
      "Convertir el activo fijo en circulante"
    ],
    correcta: 1,
    explicacion: "Diapositiva 23 del tema 1."
  },
  {
    enunciado: "La sinergia entre subsistemas significa que:",
    opciones: [
      "Los subsistemas deben funcionar aislados",
      "La empresa puede ser más productiva que si las partes actuaran de forma independiente",
      "La dirección desaparece",
      "Solo importa el subsistema financiero"
    ],
    correcta: 1,
    explicacion: "Diapositiva 23 del tema 1."
  },
  {
    enunciado: "¿Cuál de los siguientes es un subsistema funcional de la empresa encargado de adquirir los insumos necesarios para el proceso productivo?",
    opciones: [
      "Subsistema financiero",
      "Subsistema de dirección",
      "Subsistema de aprovisionamiento",
      "Subsistema de comercialización"
    ],
    correcta: 2,
    explicacion: "Diapositiva 24 del tema 1."
  },
  {
    enunciado: "¿Qué subsistema toma decisiones sobre producto, precio, promoción y distribución?",
    opciones: [
      "Aprovisionamiento",
      "Producción",
      "Comercialización",
      "Recursos humanos"
    ],
    correcta: 2,
    explicacion: "Diapositiva 24 del tema 1."
  },
  {
    enunciado: "¿Cuál de las siguientes funciones aparece entre las tareas del subsistema de dirección?",
    opciones: [
      "Amortización fiscal",
      "Planificación, organización y control de los subsistemas funcionales",
      "Fabricación directa de productos",
      "Registro exclusivo de pagos a proveedores"
    ],
    correcta: 1,
    explicacion: "Diapositiva 25 del tema 1."
  },
  {
    enunciado: "¿Qué mide la eficacia?",
    opciones: [
      "El nivel de cumplimiento de objetivos",
      "La liquidez inmediata",
      "El beneficio neto",
      "El volumen de recursos financieros"
    ],
    correcta: 0,
    explicacion: "Diapositiva 27 del tema 1."
  },
  {
    enunciado: "¿Qué mide la eficiencia?",
    opciones: [
      "El grado de endeudamiento de la empresa",
      "Si la organización utiliza la cantidad adecuada de recursos para lograr sus objetivos",
      "El número de trabajadores",
      "El crecimiento del beneficio extraordinario"
    ],
    correcta: 1,
    explicacion: "Diapositiva 27 del tema 1."
  },
  {
    enunciado: "¿Cuál de las siguientes es una función general clásica en el ámbito de la dirección de empresas?",
    opciones: [
      "Amortización",
      "Planificación",
      "Facturación",
      "Tesorería"
    ],
    correcta: 1,
    explicacion: "Diapositiva 29 del tema 1."
  },
  {
    enunciado: "Según Knight, el beneficio empresarial se justifica por:",
    opciones: [
      "La maximización automática del beneficio",
      "La propiedad colectiva del capital",
      "La intervención del Estado",
      "Los riesgos técnicos y económicos que asume el empresario"
    ],
    correcta: 3,
    explicacion: "Diapositiva 31 del tema 1."
  },
  {
    enunciado: "Según Schumpeter, el empresario es fundamentalmente:",
    opciones: [
      "Un órgano colegiado",
      "Un innovador",
      "Un mero propietario del capital",
      "Un trabajador especializado"
    ],
    correcta: 1,
    explicacion: "Diapositiva 31 del tema 1."
  },
  {
    enunciado: "Según Galbraith, la tecnoestructura es:",
    opciones: [
      "Un órgano colegiado que dirige la empresa",
      "El conjunto de accionistas minoritarios",
      "El mercado financiero que controla a la empresa",
      "El grupo de proveedores estratégicos"
    ],
    correcta: 0,
    explicacion: "Diapositiva 33 del tema 1."
  },
  {
    enunciado: "Según el tema 1, ¿cuáles son las dos categorías generales de accionistas?",
    opciones: [
      "Accionistas mayoritarios y accionistas minoritarios",
      "Accionistas de control y accionistas pasivos o simples inversores financieros",
      "Accionistas internos y accionistas externos",
      "Accionistas públicos y accionistas privados"
    ],
    correcta: 1,
    explicacion: "Diapositiva 35 del tema 1."
  },
  {
    enunciado: "En pequeñas empresas suelen coincidir normalmente las figuras de:",
    opciones: [
      "Empresario, propietario y directivo",
      "Proveedor, cliente y Estado",
      "Acreedor, deudor y auditor",
      "Alta dirección, base operativa y competencia"
    ],
    correcta: 0,
    explicacion: "Diapositiva 37 del tema 1."
  },
  {
    enunciado: "La alta dirección se encarga principalmente de:",
    opciones: [
      "Ejecutar tareas rutinarias de base operativa",
      "Fijar los grandes objetivos y controlar su cumplimiento",
      "Realizar únicamente funciones contables",
      "Representar a los proveedores"
    ],
    correcta: 1,
    explicacion: "Diapositiva 38 del tema 1."
  },
  {
    enunciado: "La dirección intermedia se caracteriza por:",
    opciones: [
      "No adoptar decisiones propias",
      "Ser el enlace jerárquico y adoptar decisiones de su nivel",
      "Coincidir siempre con los accionistas de control",
      "Estar formada solo por operarios"
    ],
    correcta: 1,
    explicacion: "Diapositiva 38 del tema 1."
  },
  {
    enunciado: "El gobierno corporativo pretende principalmente:",
    opciones: [
      "Eliminar el beneficio",
      "Sustituir a los accionistas",
      "Concretar las relaciones y controlar conflictos entre partes",
      "Reducir la producción"
    ],
    correcta: 2,
    explicacion: "Diapositiva 39 del tema 1."
  },
  {
    enunciado: "La Junta General:",
    opciones: [
      "Administra directamente la sociedad",
      "Sustituye a los trabajadores",
      "Aprueba precios de venta de cada producto",
      "Nombra a los administradores"
    ],
    correcta: 3,
    explicacion: "Diapositiva 40 del tema 1."
  },
  {
    enunciado: "Según la Ley de Sociedades de Capital explicada en el tema, los órganos de administración:",
    opciones: [
      "No son necesarios ni permanentes",
      "Ejercen la gestión y representación de la sociedad",
      "Solo pueden ser unipersonales",
      "Son nombrados por los proveedores"
    ],
    correcta: 1,
    explicacion: "Diapositiva 40 del tema 1."
  },
  {
    enunciado: "Una OPA se menciona en el tema 1 como:",
    opciones: [
      "Una herramienta de responsabilidad social",
      "Un mecanismo de control vinculado a tomas de control hostiles",
      "Una forma de financiación exclusivamente pública",
      "Una técnica de cálculo del beneficio neto"
    ],
    correcta: 1,
    explicacion: "Diapositiva 41 del tema 1."
  },
  {
    enunciado: "¿Qué caracteriza al modelo anglosajón de gobierno corporativo?",
    opciones: [
      "Una concentración accionarial muy importante",
      "Un sistema monista dominado por participaciones cruzadas",
      "Un accionariado muy disperso",
      "La ausencia de directivos profesionales"
    ],
    correcta: 2,
    explicacion: "Diapositiva 42 del tema 1."
  },
  {
    enunciado: "¿Qué caracteriza al modelo alemán de gobierno corporativo?",
    opciones: [
      "Accionariado muy disperso",
      "Concentración accionarial muy importante",
      "Predominio absoluto de las cooperativas",
      "Ausencia de accionistas minoritarios"
    ],
    correcta: 1,
    explicacion: "Diapositiva 42 del tema 1."
  },
  {
    enunciado: "El modelo japonés de gobierno corporativo se caracteriza por:",
    opciones: [
      "Una dispersión extrema del capital sin dirección estable",
      "Un sistema monista dominado por directivos con participaciones cruzadas",
      "La prohibición de participaciones accionariales cruzadas",
      "La inexistencia de presidente ejecutivo"
    ],
    correcta: 1,
    explicacion: "Diapositiva 42 del tema 1."
  },
  {
    enunciado: "La definición formal de RSC del tema 1 comienza diciendo que es un:",
    opciones: [
      "Sistema de maximización del beneficio",
      "Conjunto de obligaciones y compromisos legales y éticos",
      "Modelo de control exclusivo de accionistas",
      "Mecanismo contable de certificación"
    ],
    correcta: 1,
    explicacion: "Diapositiva 47 del tema 1."
  },
  {
    enunciado: "La RSC afecta, según la definición formal del tema 1, a organizaciones:",
    opciones: [
      "Solo privadas y con ánimo de lucro",
      "Solo públicas",
      "Públicas o privadas, con o sin ánimo de lucro",
      "Exclusivamente multinacionales"
    ],
    correcta: 2,
    explicacion: "Diapositiva 47 del tema 1."
  },
  {
    enunciado: "Según el 'Libro Verde sobre la RSC' de la Unión Europea, la RSC se define como:",
    opciones: [
      "La integración voluntaria de preocupaciones sociales y medioambientales en operaciones comerciales y relaciones con interlocutores",
      "La obligación legal de donar beneficios",
      "La subordinación de la empresa al Estado",
      "La protección exclusiva del accionista"
    ],
    correcta: 0,
    explicacion: "Diapositiva 48 del tema 1."
  },
  {
    enunciado: "¿Cuáles son los ámbitos de la RSC según el tema?",
    opciones: [
      "Jurídico, contable y fiscal",
      "Económicos, sociales y ambientales",
      "Local, nacional y europeo",
      "Internos, contables y tecnológicos"
    ],
    correcta: 1,
    explicacion: "Diapositiva 51 del tema 1."
  },
  {
    enunciado: "Según el tema 1, entre los stakeholders de la empresa pueden encontrarse:",
    opciones: [
      "Solo los empleados",
      "Solo los inversores",
      "Empleados, clientes, proveedores e inversores",
      "Únicamente las administraciones públicas"
    ],
    correcta: 2,
    explicacion: "Diapositiva 51 del tema 1."
  },
  {
    enunciado: "Una de las dimensiones de la RSC mencionadas expresamente en el tema 1 es la dimensión:",
    opciones: [
      "Interna",
      "Arancelaria",
      "Monetaria",
      "Jurisdiccional"
    ],
    correcta: 0,
    explicacion: "Diapositiva 51 del tema 1."
  },
  {
    enunciado: "El desarrollo sostenible se define en el tema como aquel que:",
    opciones: [
      "Garantiza crecimiento económico ilimitado",
      "Aumenta la productividad industrial",
      "Reduce exclusivamente la contaminación urbana",
      "Satisface las necesidades del presente sin comprometer la capacidad de las generaciones futuras de satisfacer las suyas"
    ],
    correcta: 3,
    explicacion: "Diapositiva 53 del tema 1."
  },
  {
    enunciado: "El “triple objetivo” que se ha visto en el tema 1 es:",
    opciones: [
      "Crecer, exportar e innovar",
      "Ser económicamente viable, socialmente beneficiosa y ambientalmente responsable",
      "Reducir costes, subir precios y aumentar ventas",
      "Mejorar liquidez, solvencia y rentabilidad"
    ],
    correcta: 1,
    explicacion: "Diapositiva 61 del tema 1."
  },
  {
    enunciado: "Según el tema, los stakeholders son:",
    opciones: [
      "Solo los accionistas de control",
      "Solo clientes y proveedores",
      "Los grupos y personas que afectan a la empresa o son afectados por ella",
      "Únicamente los empleados"
    ],
    correcta: 2,
    explicacion: "Diapositiva 90 del tema 1."
  },
  {
    enunciado: "Según Carroll, una de las cuatro caras de la responsabilidad social de la empresa es:",
    opciones: [
      "Obedecer la ley",
      "Eliminar toda financiación ajena",
      "Prescindir de los stakeholders",
      "Maximizar la producción física"
    ],
    correcta: 0,
    explicacion: "Diapositiva 91 del tema 1."
  },
  {
    enunciado: "La ecuación básica del patrimonio empresarial es:",
    opciones: [
      "Bienes + Obligaciones = Derechos + Patrimonio neto",
      "Bienes + Derechos - Obligaciones = Patrimonio neto",
      "Activo corriente - Activo no corriente = Pasivo",
      "Patrimonio neto + Ingresos = Costes"
    ],
    correcta: 1,
    explicacion: "Diapositiva 7 del tema 2."
  },
  {
    enunciado: "¿Cuál de las siguientes NO es una de las tres categorías del patrimonio empresarial?",
    opciones: [
      "Bienes",
      "Derechos",
      "Obligaciones",
      "Dividendos"
    ],
    correcta: 3,
    explicacion: "Diapositiva 7 del tema 2."
  },
  {
    enunciado: "La masa patrimonial de pasivo engloba:",
    opciones: [
      "Bienes y derechos de uso duradero",
      "Resultados acumulados no distribuidos",
      "Deudas u obligaciones pendientes de pago",
      "Solo el efectivo y otros activos líquidos"
    ],
    correcta: 2,
    explicacion: "Diapositiva 10 del tema 2."
  },
  {
    enunciado: "El neto patrimonial se expresa en el tema como:",
    opciones: [
      "Activo + Pasivo",
      "Activo corriente - Pasivo no corriente",
      "Recursos permanentes + activo fijo",
      "Activo - Pasivo"
    ],
    correcta: 3,
    explicacion: "Diapositiva 11 del tema 2."
  },
  {
    enunciado: "Los recursos permanentes de la empresa están formados por:",
    opciones: [
      "Patrimonio neto más pasivo no corriente",
      "Activo corriente más pasivo corriente",
      "Solo pasivo corriente",
      "Existencias más tesorería"
    ],
    correcta: 0,
    explicacion: "Diapositiva 12 del tema 2."
  },
  {
    enunciado: "El activo no corriente está formado por activos que:",
    opciones: [
      "Se esperan vender o realizar siempre antes de un año",
      "Están destinados a servir de forma duradera en la empresa",
      "Solo incluyen tesorería y bancos",
      "Se corresponden exclusivamente con existencias"
    ],
    correcta: 1,
    explicacion: "Diapositiva 13 del tema 2."
  },
  {
    enunciado: "¿Cuál de los siguientes elementos pertenece al activo no corriente?",
    opciones: [
      "Existencias",
      "Clientes",
      "Inmovilizado material",
      "Caja"
    ],
    correcta: 2,
    explicacion: "Diapositiva 13 del tema 2."
  },
  {
    enunciado: "Dentro del activo corriente se incluyen:",
    opciones: [
      "Existencias, deudores y efectivo",
      "Solo edificios y maquinaria",
      "Únicamente las reservas",
      "Solo deudas a largo plazo"
    ],
    correcta: 0,
    explicacion: "Diapositiva 13 del tema 2."
  },
  {
    enunciado: "La situación en la que el activo circulante coincide con el pasivo circulante es:",
    opciones: [
      "Iliquidez",
      "Máxima estabilidad",
      "Quiebra",
      "Expansión"
    ],
    correcta: 0,
    explicacion: "Diapositiva 32 del tema 2."
  },
  {
    enunciado: "Cuando el activo circulante es superior al pasivo circulante, estamos en una situación de:",
    opciones: [
      "Situación normal de equilibrio financiero",
      "Iliquidez necesaria",
      "Quiebra técnica inmediata",
      "Máxima inestabilidad"
    ],
    correcta: 0,
    explicacion: "Diapositiva 31 del tema 2."
  },
  {
    enunciado: "¿Cuándo se da la situación de máxima estabilidad?",
    opciones: [
      "Cuando el activo circulante coincide con el pasivo circulante",
      "Cuando todo el activo está financiado con recursos propios y la empresa no tiene deudas",
      "Cuando el patrimonio neto es negativo",
      "Cuando la empresa tiene más pasivo corriente que activo corriente"
    ],
    correcta: 1,
    explicacion: "Diapositiva 34 del tema 2."
  },
  {
    enunciado: "La liquidez de la empresa se define como:",
    opciones: [
      "La capacidad de generar beneficios extraordinarios",
      "La capacidad de cumplir con sus obligaciones a corto plazo",
      "La ausencia total de deudas",
      "La proporción entre ventas y activos fijos"
    ],
    correcta: 1,
    explicacion: "Diapositiva 35 del tema 2."
  },
  {
    enunciado: "El fondo de maniobra o capital circulante es:",
    opciones: [
      "Activo no corriente + patrimonio neto",
      "Pasivo corriente - activo circulante",
      "Beneficio económico - beneficio neto",
      "Activo circulante - pasivo circulante"
    ],
    correcta: 3,
    explicacion: "Diapositiva 36 del tema 2."
  },
  {
    enunciado: "Además de como activo circulante menos pasivo circulante, el capital circulante también puede expresarse como:",
    opciones: [
      "Patrimonio neto menos beneficio neto",
      "Recursos permanentes menos activo no corriente",
      "Activo total menos pasivo total",
      "Existencias menos proveedores"
    ],
    correcta: 1,
    explicacion: "Diapositiva 36 del tema 2."
  },
  {
    enunciado: "El ciclo corto de explotación abarca, de forma resumida, el período que media entre:",
    opciones: [
      "La constitución de la sociedad y su disolución",
      "La salida de tesorería para comprar y la recuperación mediante venta y cobro",
      "La compra del inmovilizado y su amortización total",
      "La aprobación del presupuesto y el cierre contable"
    ],
    correcta: 1,
    explicacion: "Diapositiva 37 del tema 2."
  },
  {
    enunciado: "En empresas comerciales, el período medio de maduración es:",
    opciones: [
      "PMM = Pmds + Pc - Pp",
      "PMM = Pp + Pc + Pmds",
      "PMM = Pc - Pmds",
      "PMM = Pmds - Pc + Pp"
    ],
    correcta: 0,
    explicacion: "Diapositiva 38 del tema 2."
  },
  {
    enunciado: "Si CC > CCN, según el tema 2, puede interpretarse que la empresa:",
    opciones: [
      "Tiene problemas seguros de quiebra",
      "Mantiene recursos ociosos",
      "No puede pagar a proveedores",
      "Presenta patrimonio neto negativo"
    ],
    correcta: 1,
    explicacion: "Diapositiva 44 del tema 2."
  },
  {
    enunciado: "La ratio de disponibilidad ordinaria se calcula como:",
    opciones: [
      "Activo corriente / pasivo corriente",
      "Cuentas financieras / pasivo circulante",
      "(Cuentas financieras + deudores) / activo total",
      "Activo total / pasivo total"
    ],
    correcta: 1,
    explicacion: "Diapositiva 46 del tema 2."
  },
  {
    enunciado: "Un valor orientativo considerado normal para la ratio de tesorería es aproximadamente:",
    opciones: [
      "0,8",
      "2,5",
      "5",
      "0,1"
    ],
    correcta: 0,
    explicacion: "Diapositiva 46 del tema 2."
  },
  {
    enunciado: "La ratio de solvencia total es:",
    opciones: [
      "Activo total / pasivo total",
      "Patrimonio neto / activo total",
      "Ventas / pasivo corriente",
      "BAIT / impuestos"
    ],
    correcta: 0,
    explicacion: "Diapositiva 49 del tema 2."
  },
  {
    enunciado: "La ratio de solvencia total también se denomina:",
    opciones: [
      "Ratio de productividad marginal",
      "Ratio de garantía o distancia a la quiebra",
      "Acid test",
      "Margen de cobertura"
    ],
    correcta: 1,
    explicacion: "Diapositiva 49 del tema 2."
  },
  {
    enunciado: "Un índice de solvencia total por debajo de 1 implica que la empresa:",
    opciones: [
      "Está en situación de quiebra",
      "Tiene máxima estabilidad",
      "Mantiene exceso de liquidez",
      "No tiene pasivo corriente"
    ],
    correcta: 0,
    explicacion: "Diapositiva 49 del tema 2."
  },
  {
    enunciado: "El beneficio es:",
    opciones: [
      "La diferencia entre activo y pasivo",
      "Un excedente económico resultante de la diferencia entre ingresos y gastos",
      "El valor de los fondos propios",
      "El resultado de restar activo fijo al pasivo total"
    ],
    correcta: 1,
    explicacion: "Diapositiva 52 del tema 2."
  },
  {
    enunciado: "El BAIT es:",
    opciones: [
      "Beneficio después de impuestos",
      "Beneficio antes de impuestos y después de intereses",
      "Beneficio neto distribuible",
      "Beneficio antes de intereses e impuestos"
    ],
    correcta: 3,
    explicacion: "Diapositiva 53 del tema 2."
  },
  {
    enunciado: "El BAI se obtiene a partir del BAIT restando:",
    opciones: [
      "Los costes variables",
      "Los costes fijos vinculados con la estructura financiera",
      "Los impuestos sobre beneficios",
      "Las existencias finales"
    ],
    correcta: 1,
    explicacion: "Diapositiva 53 del tema 2. Cabe destacar que en dicha diapositiva se está agrupando la definición del concepto con los sustraendos para obtener el siguiente concepto."
  },
  {
    enunciado: "El beneficio neto (BN) se obtiene restando al BAI:",
    opciones: [
      "Las reservas",
      "El impuesto sobre beneficios",
      "Los gastos de personal",
      "La amortización acumulada"
    ],
    correcta: 1,
    explicacion: "Diapositiva 53 del tema 2."
  },
  {
    enunciado: "El beneficio económico (BAIT) depende únicamente de:",
    opciones: [
      "La estructura financiera y el impuesto sobre beneficios",
      "Los dividendos a cuenta",
      "El pasivo corriente",
      "La actividad realizada y la estructura productiva y de distribución"
    ],
    correcta: 3,
    explicacion: "Diapositiva 54 del tema 2."
  },
  {
    enunciado: "¿Qué tiene en cuenta el beneficio financiero (BN) además del impuesto sobre beneficios?",
    opciones: [
      "Solo la estructura productiva y de distribución",
      "Los gastos financieros derivados de la financiación ajena",
      "Únicamente las ventas netas",
      "El punto muerto de la empresa"
    ],
    correcta: 1,
    explicacion: "Diapositiva 54 del tema 2."
  },
  {
    enunciado: "¿Qué diferencia se ha visto entre coste y gasto?",
    opciones: [
      "Son exactamente lo mismo",
      "El gasto es siempre mayor que el coste",
      "El gasto es la expresión monetaria de la adquisición de factores, y el coste es la medida y valoración del consumo realizado o previsto",
      "El coste solo existe en empresas industriales"
    ],
    correcta: 2,
    explicacion: "Diapositiva 61 del tema 2."
  },
  {
    enunciado: "¿Qué expresión es correcta para el coste total?",
    opciones: [
      "CT = CF + CV",
      "CT = CF - CV",
      "CT = CV / Q",
      "CT = p x Q"
    ],
    correcta: 0,
    explicacion: "Diapositiva 63 del tema 2."
  },
  {
    enunciado: "El coste medio o unitario se calcula como:",
    opciones: [
      "CT x Q",
      "CT / Q",
      "ΔCT / ΔQ",
      "CF / CV"
    ],
    correcta: 1,
    explicacion: "Diapositiva 66 del tema 2."
  },
  {
    enunciado: "El coste marginal representa:",
    opciones: [
      "El coste total de toda la producción",
      "El incremento del coste total al aumentar la producción en una unidad",
      "El precio mínimo de venta",
      "La diferencia entre activo y pasivo"
    ],
    correcta: 1,
    explicacion: "Diapositiva 67 del tema 2."
  },
  {
    enunciado: "Matemáticamente, el coste medio alcanza su mínimo en:",
    opciones: [
      "El punto donde corta al coste marginal",
      "El máximo del coste fijo",
      "El valor cero de las existencias",
      "El punto muerto"
    ],
    correcta: 0,
    explicacion: "Diapositiva 70 del tema 2."
  },
  {
    enunciado: "Según la certeza de la vinculación del consumo de factores de los productos, ¿qué tipos de costes existen?",
    opciones: [
      "Costes fijos y costes variables",
      "Costes directos y costes indirectos",
      "Costes explícitos y costes implícitos",
      "Costes reales y costes estándar"
    ],
    correcta: 1,
    explicacion: "Diapositiva 71 del tema 2."
  },
  {
    enunciado: "¿Qué es el punto muerto o umbral de rentabilidad?",
    opciones: [
      "El volumen de operaciones en el que la empresa cubre todos sus costes fijos y variables",
      "El punto en que el activo iguala al pasivo",
      "El valor del patrimonio neto al inicio del ejercicio",
      "El momento en el que desaparece el coste fijo"
    ],
    correcta: 0,
    explicacion: "Diapositiva 72 del tema 2."
  },
  {
    enunciado: "Por debajo del punto muerto, la empresa:",
    opciones: [
      "Obtiene beneficios positivos",
      "Cubre todos sus costes fijos y variables",
      "Incurre en pérdidas",
      "Alcanza el máximo beneficio"
    ],
    correcta: 2,
    explicacion: "Diapositiva 72 del tema 2."
  },
  {
    enunciado: "El margen de cobertura o de contribución viene dado por:",
    opciones: [
      "CF - CVMe",
      "p - CVMe",
      "Activo total / pasivo total",
      "BAI - impuestos"
    ],
    correcta: 1,
    explicacion: "Diapositiva 75 del tema 2."
  },
  {
    enunciado: "Atendiendo a su finalidad, una inversión para mejorar la posición en el mercado sería una inversión:",
    opciones: [
      "Estratégica",
      "De tesorería",
      "Pasiva",
      "Implícita"
    ],
    correcta: 0,
    explicacion: "Diapositiva 90 del tema 2."
  },
  {
    enunciado: "Atendiendo a las relaciones entre las inversiones, ¿qué tipos de inversiones se distinguen el tema 2?",
    opciones: [
      "Inversiones de renovación, de expansión y estratégicas",
      "Inversiones complementarias, sustitutivas e independientes",
      "Inversiones a corto plazo, a largo plazo y no simples",
      "Inversiones productivas, financieras y comerciales"
    ],
    correcta: 1,
    explicacion: "Diapositiva 90 del tema 2."
  },
  {
    enunciado: "¿Cuál es la característica de una inversión simple?",
    opciones: [
      "Todos los flujos netos de caja son negativos",
      "El flujo inicial es positivo por definición",
      "Todos los flujos netos de caja son positivos salvo el flujo inicial, que es negativo por definición",
      "Incluye al menos dos desembolsos iniciales negativos obligatorios"
    ],
    correcta: 2,
    explicacion: "Diapositiva 91 del tema 2."
  },
  {
    enunciado: "Una inversión no simple es aquella en la que:",
    opciones: [
      "Todos los flujos, incluido el inicial, son positivos",
      "Junto al desembolso inicial existe al menos un flujo neto de caja negativo adicional",
      "El activo invertido siempre es corriente",
      "Solo hay un flujo final positivo"
    ],
    correcta: 1,
    explicacion: "Diapositiva 91 del tema 2."
  },
  {
    enunciado: "(Primera Prueba 25-26) Una organización se caracteriza por:",
    opciones: [
      "Personas reunidas sin objetivos",
      "Personas coordinadas para lograr objetivos comunes",
      "Un grupo informal",
      "Una empresa con ánimo de lucro"
    ],
    correcta: 1,
    explicacion: "Diapositiva 4 del tema 1.",
    grupo: "primera-prueba-25-26"
  },
  {
    enunciado: "(Primera Prueba 25-26) La empresa es un sistema porque:",
    opciones: [
      "No interactúa con el entorno",
      "Está formada por elementos interrelacionados",
      "No tiene límites",
      "No requiere control"
    ],
    correcta: 1,
    explicacion: "Diapositiva 18 del tema 1.",
    grupo: "primera-prueba-25-26"
  },
  {
    enunciado: "(Primera Prueba 25-26) El subsistema de aprovisionamiento se encarga de:",
    opciones: [
      "Transformar inputs",
      "Comprar insumos",
      "Diseñar campañas",
      "Seleccionar personal"
    ],
    correcta: 1,
    explicacion: "Diapositiva 24 del tema 1.",
    grupo: "primera-prueba-25-26"
  },
  {
    enunciado: "(Primera Prueba 25-26) La eficacia consiste en:",
    opciones: [
      "Lograr objetivos",
      "Reducir recursos",
      "Aumentar producción",
      "Minimizar costes"
    ],
    correcta: 0,
    explicacion: "Diapositiva 27 del tema 1.",
    grupo: "primera-prueba-25-26"
  },
  {
    enunciado: "(Primera Prueba 25-26) La eficiencia consiste en:",
    opciones: [
      "Lograr objetivos sin importar recursos",
      "Usar bien los recursos para lograr objetivos",
      "Reducir costes sin producir",
      "Aumentar ventas"
    ],
    correcta: 1,
    explicacion: "Diapositiva 27 del tema 1.",
    grupo: "primera-prueba-25-26"
  },
  {
    enunciado: "(Primera Prueba 25-26) El patrimonio empresarial incluye:",
    opciones: [
      "Bienes y derechos",
      "Bienes, derechos y obligaciones",
      "Solo bienes",
      "Solo derechos"
    ],
    correcta: 1,
    explicacion: "Diapositiva 7 del tema 2.",
    grupo: "primera-prueba-25-26"
  },
  {
    enunciado: "(Primera Prueba 25-26) El activo corriente incluye:",
    opciones: [
      "Maquinaria",
      "Existencias, clientes y tesorería",
      "Terrenos",
      "Inversiones a largo plazo"
    ],
    correcta: 1,
    explicacion: "Diapositivas 16, 17 y 18 del tema 2.",
    grupo: "primera-prueba-25-26"
  },
  {
    enunciado: "(Primera Prueba 25-26) El pasivo corriente incluye:",
    opciones: [
      "Deudas a largo plazo",
      "Deudas con vencimiento inferior a un año",
      "Patrimonio neto",
      "Activos financieros"
    ],
    correcta: 1,
    explicacion: "Diapositiva 23 del tema 2.",
    grupo: "primera-prueba-25-26"
  },
  {
    enunciado: "(Primera Prueba 25-26) El fondo de maniobra es:",
    opciones: [
      "Activo corriente - Pasivo corriente",
      "Activo total - Pasivo total",
      "Activo no corriente - Pasivo corriente",
      "Pasivo corriente - Activo corriente"
    ],
    correcta: 0,
    explicacion: "Diapositiva 36 del tema 2.",
    grupo: "primera-prueba-25-26"
  },
  {
    enunciado: "(Primera Prueba 25-26) Fondo de maniobra positivo implica:",
    opciones: [
      "Insolvencia",
      "Capacidad de pago a corto plazo",
      "Patrimonio neto negativo",
      "Exceso de deuda"
    ],
    correcta: 1,
    explicacion: "Diapositiva 35 del tema 2.",
    grupo: "primera-prueba-25-26"
  },
  {
    enunciado: "(Primera Prueba 25-26) El ciclo de explotación incluye:",
    opciones: [
      "Solo la venta",
      "Compra → Producción → Venta → Cobro",
      "Solo la producción",
      "Solo el cobro"
    ],
    correcta: 1,
    explicacion: "Diapositiva 37 del tema 2.",
    grupo: "primera-prueba-25-26"
  },
  {
    enunciado: "(Primera Prueba 25-26) El periodo medio de maduración financiero es:",
    opciones: [
      "PMM económico - periodo de pago",
      "PMM económico + periodo de pago",
      "Periodo de cobro - periodo de pago",
      "Periodo de almacenamiento + periodo de pago"
    ],
    correcta: 0,
    explicacion: "Diapositiva 38 del tema 2.",
    grupo: "primera-prueba-25-26"
  },
  {
    enunciado: "(Primera Prueba 25-26) El ratio de liquidez general mide:",
    opciones: [
      "Solvencia inmediata",
      "Capacidad de cubrir deudas a corto plazo con activo corriente",
      "Rentabilidad",
      "Endeudamiento"
    ],
    correcta: 1,
    explicacion: "Diapositiva 47 del tema 2.",
    grupo: "primera-prueba-25-26"
  },
  {
    enunciado: "(Primera Prueba 25-26) El ratio de tesorería mide:",
    opciones: [
      "Capacidad inmediata de pago",
      "Solvencia a largo plazo",
      "Rotación de existencias",
      "Rentabilidad financiera"
    ],
    correcta: 0,
    explicacion: "Diapositiva 46 del tema 2.",
    grupo: "primera-prueba-25-26"
  },
  {
    enunciado: "(Primera Prueba 25-26) El beneficio económico incluye:",
    opciones: [
      "Solo ingresos financieros",
      "Ingresos y costes de explotación",
      "Solo ingresos de explotación",
      "Solo costes variables"
    ],
    correcta: 1,
    explicacion: "Diapositiva 54 del tema 2.",
    grupo: "primera-prueba-25-26"
  },
  {
    enunciado: "(Primera Prueba 25-26) El beneficio financiero se obtiene:",
    opciones: [
      "Antes de impuestos",
      "Después de restar gastos financieros e impuestos",
      "Sumando amortizaciones",
      "Antes de gastos financieros"
    ],
    correcta: 1,
    explicacion: "Diapositiva 54 del tema 2.",
    grupo: "primera-prueba-25-26"
  },
  {
    enunciado: "(Primera Prueba 25-26) Una inversión amplia incluye:",
    opciones: [
      "Solo inmovilizado",
      "Activos corrientes y no corrientes",
      "Solo activos financieros",
      "Solo activos intangibles"
    ],
    correcta: 1,
    explicacion: "Diapositiva 89 del tema 2.",
    grupo: "primera-prueba-25-26"
  },
  {
    enunciado: "(Primera Prueba 25-26) La capitalización consiste en:",
    opciones: [
      "Llevar un valor futuro al presente",
      "Llevar un valor presente al futuro",
      "Reducir intereses",
      "Eliminar riesgo"
    ],
    correcta: 1,
    explicacion: "Diapositiva 93 del tema 2.",
    grupo: "primera-prueba-25-26"
  },
  {
    enunciado: "(Primera Prueba 25-26) La actualización consiste en:",
    opciones: [
      "Llevar un valor presente al futuro",
      "Llevar un valor futuro al presente",
      "Calcular el fondo de maniobra",
      "Calcular el PMM"
    ],
    correcta: 1,
    explicacion: "Diapositiva 93 del tema 2.",
    grupo: "primera-prueba-25-26"
  },
  {
    enunciado: "(Primera Prueba 25-26) La RSC implica:",
    opciones: [
      "Cumplimiento legal mínimo",
      "Integración de criterios sociales y ambientales",
      "Reducción de costes laborales",
      "Eliminación de competencia"
    ],
    correcta: 1,
    explicacion: "Diapositiva 48 del tema 1.",
    grupo: "primera-prueba-25-26"
  },
  {
    enunciado: "(Primera Prueba 25-26) El activo no corriente incluye:",
    opciones: [
      "Existencias",
      "Maquinaria y edificios",
      "Tesorería",
      "Clientes"
    ],
    correcta: 1,
    explicacion: "Diapositiva 13 del tema 2.",
    grupo: "primera-prueba-25-26"
  },
  {
    enunciado: "(Primera Prueba 25-26) El pasivo no corriente incluye:",
    opciones: [
      "Deudas con vencimiento superior a un año",
      "Proveedores",
      "Tesorería",
      "Existencias"
    ],
    correcta: 0,
    explicacion: "Diapositiva 21 del tema 2.",
    grupo: "primera-prueba-25-26"
  },
  {
    enunciado: "(Primera Prueba 25-26) El patrimonio neto representa:",
    opciones: [
      "Deudas",
      "Recursos propios",
      "Activos financieros",
      "Existencias"
    ],
    correcta: 1,
    explicacion: "Diapositiva 19 del tema 2.",
    grupo: "primera-prueba-25-26"
  },
  {
    enunciado: "(Primera Prueba 25-26) La situación de máxima estabilidad se da cuando:",
    opciones: [
      "Todo el activo se financia con recursos propios",
      "El pasivo corriente es mayor que el activo corriente",
      "El patrimonio neto es negativo",
      "La empresa tiene muchas deudas"
    ],
    correcta: 0,
    explicacion: "Diapositiva 34 del tema 2.",
    grupo: "primera-prueba-25-26"
  },
  {
    enunciado: "(Primera Prueba 25-26) El PMM económico incluye:",
    opciones: [
      "Solo el periodo de cobro",
      "Almacenamiento + fabricación + venta + cobro",
      "Solo el periodo de pago",
      "Solo fabricación"
    ],
    correcta: 1,
    explicacion: "Diapositiva 37 del tema 2.",
    grupo: "primera-prueba-25-26"
  },
  {
    enunciado: "(Primera Prueba 25-26) El PMM financiero indica:",
    opciones: [
      "Tiempo que la empresa financia a proveedores",
      "Tiempo que la empresa necesita financiar su ciclo",
      "Tiempo de amortización",
      "Tiempo de renovación del inmovilizado"
    ],
    correcta: 1,
    explicacion: "Diapositiva 37 del tema 2.",
    grupo: "primera-prueba-25-26"
  },
  {
    enunciado: "(Primera Prueba 25-26) El ratio de disponibilidad inmediata es:",
    opciones: [
      "Activo corriente / Pasivo corriente",
      "Tesorería / Pasivo corriente",
      "Existencias / Pasivo corriente",
      "Patrimonio neto / Activo total"
    ],
    correcta: 1,
    explicacion: "Diapositiva 46 del tema 2.",
    grupo: "primera-prueba-25-26"
  },
  {
    enunciado: "(Primera Prueba 25-26) El beneficio empresarial es:",
    opciones: [
      "Ventas totales",
      "Ingresos - gastos",
      "Activo - pasivo",
      "Patrimonio neto"
    ],
    correcta: 1,
    explicacion: "Diapositiva 52 del tema 2.",
    grupo: "primera-prueba-25-26"
  },
  {
    enunciado: "(Primera Prueba 25-26) La empresa como sistema abierto:",
    opciones: [
      "No recibe información",
      "Interactúa con el entorno",
      "No tiene retroalimentación",
      "No tiene límites"
    ],
    correcta: 1,
    explicacion: "Diapositiva 19 del tema 1.",
    grupo: "primera-prueba-25-26"
  },
  {
    enunciado: "(Primera Prueba 25-26) Un stakeholder primario es:",
    opciones: [
      "Un grupo sin influencia",
      "Un grupo esencial para la supervivencia",
      "Un competidor",
      "Un grupo externo sin interés económico"
    ],
    correcta: 1,
    explicacion: "En ninguna diapositiva sale definido explícitamente lo que es un stakeholder primario, pero la más cercana podría ser la diapositiva 90 del tema 1.",
    grupo: "primera-prueba-25-26"
  }
];

const quiz = document.getElementById("quiz");

// Estado de cada pregunta: null = no respondida, número = opción elegida
const respuestasUsuario = Array(preguntas.length).fill(null);

// Orden visible actual de las preguntas
let ordenPreguntas = preguntas.map((_, i) => i);

// Estado de simulacro
let simulacroActivo = false;
let primeraPruebaActiva = false;
let ordenAnteriorSimulacro = [...ordenPreguntas];

// Barra superior
const barra = document.createElement("div");
barra.style.marginBottom = "20px";

const botonAleatorio = document.createElement("button");
botonAleatorio.textContent = "Mostrar en orden aleatorio";
botonAleatorio.style.marginRight = "10px";

const botonSimulacro = document.createElement("button");
botonSimulacro.textContent = "Simulacro de Examen";
botonSimulacro.style.marginRight = "10px";

const botonPrimeraPrueba = document.createElement("button");
botonPrimeraPrueba.textContent = "Primera Prueba 25-26";
botonPrimeraPrueba.style.marginRight = "10px";

const botonVolver = document.createElement("button");
botonVolver.textContent = "Volver";
botonVolver.style.display = "none";
botonVolver.style.marginRight = "10px";

const contador = document.createElement("p");
contador.style.margin = "10px 0 0 0";
contador.style.fontWeight = "bold";

quiz.before(barra);
barra.appendChild(botonAleatorio);
barra.appendChild(botonSimulacro);
barra.appendChild(botonPrimeraPrueba);
barra.appendChild(botonVolver);
barra.appendChild(contador);

// Botón final de reinicio
const botonReiniciar = document.createElement("button");
botonReiniciar.textContent = "Borrar respuestas y empezar de nuevo";
botonReiniciar.style.marginTop = "20px";

// Botón para terminar y ver resultados
const botonTerminar = document.createElement("button");
botonTerminar.textContent = "He terminado";
botonTerminar.style.marginTop = "20px";
botonTerminar.style.marginRight = "10px";
botonTerminar.style.display = "none";

// Caja de resultados finales
const resultadoFinal = document.createElement("div");
resultadoFinal.className = "explicacion";
resultadoFinal.style.display = "none";
resultadoFinal.style.marginTop = "20px";

function mezclar(array) {
  const copia = [...array];
  for (let i = copia.length - 1; i > 0; i--) {
    const j = Math.floor(Math.random() * (i + 1));
    [copia[i], copia[j]] = [copia[j], copia[i]];
  }
  return copia;
}

function actualizarContador() {
  let acertadas = 0;
  let respondidas = 0;

  const indicesVisibles = new Set(ordenPreguntas);

  preguntas.forEach((pregunta, i) => {
    if (!indicesVisibles.has(i)) return;

    if (respuestasUsuario[i] !== null) {
      respondidas++;
      if (respuestasUsuario[i] === pregunta.correcta) {
        acertadas++;
      }
    }
  });
}

function mostrarResultados() {
  let acertadas = 0;
  let falladas = 0;
  let respondidas = 0;

  const indicesVisibles = new Set(ordenPreguntas);

  preguntas.forEach((pregunta, i) => {
    if (!indicesVisibles.has(i)) return;

    if (respuestasUsuario[i] !== null) {
      respondidas++;

      if (respuestasUsuario[i] === pregunta.correcta) {
        acertadas++;
      } else {
        falladas++;
      }
    }
  });

  const total = ordenPreguntas.length;
  const notaSinPenalizacion = (10 * acertadas) / total;
  const notaConPenalizacion = Math.max(0, 10 * ((acertadas - falladas / 2) / total));

  resultadoFinal.innerHTML = `
    <strong>Resultados:</strong><br>
    Has respondido ${respondidas} de ${total} preguntas.<br>
    Has acertado ${acertadas} de ${total}.<br>
    Nota sin penalización: ${notaSinPenalizacion.toFixed(2)} / 10.<br>
    Nota con penalización de 1/2 por fallo (esta es la que se usa en el examen): ${notaConPenalizacion.toFixed(2)} / 10 (mínimo 0).
  `;
  resultadoFinal.style.display = "block";
}

function renderQuiz() {
  quiz.innerHTML = "";

  ordenPreguntas.forEach((indiceReal) => {
    const pregunta = preguntas[indiceReal];

    const contenedor = document.createElement("section");
    contenedor.className = "pregunta";

    const enunciado = document.createElement("h2");
    enunciado.className = "enunciado";
    enunciado.textContent = `${ordenPreguntas.indexOf(indiceReal) + 1}. ${pregunta.enunciado}`;
    contenedor.appendChild(enunciado);

    const opcionesDiv = document.createElement("div");
    opcionesDiv.className = "opciones";

    const explicacion = document.createElement("div");
    explicacion.className = "explicacion";

    pregunta.opciones.forEach((textoOpcion, indiceOpcion) => {
      const boton = document.createElement("button");
      boton.className = "opcion";
      boton.textContent = textoOpcion;

      const respuestaGuardada = respuestasUsuario[indiceReal];

      if (respuestaGuardada !== null) {
        boton.disabled = true;

        if (indiceOpcion === pregunta.correcta) {
          boton.classList.add("correcta");
        }

        if (indiceOpcion === respuestaGuardada && respuestaGuardada !== pregunta.correcta) {
          boton.classList.add("incorrecta");
        }

        explicacion.innerHTML = `<strong>Explicación:</strong> ${pregunta.explicacion}`;
        explicacion.style.display = "block";
      }

      boton.addEventListener("click", () => {
        if (respuestasUsuario[indiceReal] !== null) return;

        respuestasUsuario[indiceReal] = indiceOpcion;

        renderQuiz();
        actualizarContador();

        if (resultadoFinal.style.display === "block") {
          mostrarResultados();
        }
      });

      opcionesDiv.appendChild(boton);
    });

    contenedor.appendChild(opcionesDiv);
    contenedor.appendChild(explicacion);
    quiz.appendChild(contenedor);
  });

  botonTerminar.style.display = "inline-block";

  quiz.appendChild(botonTerminar);
  quiz.appendChild(resultadoFinal);
  quiz.appendChild(botonReiniciar);
}

botonAleatorio.addEventListener("click", () => {
  ordenPreguntas = mezclar(ordenPreguntas);
  renderQuiz();
});

botonSimulacro.addEventListener("click", () => {
  ordenAnteriorSimulacro = [...ordenPreguntas];

  for (let i = 0; i < respuestasUsuario.length; i++) {
    respuestasUsuario[i] = null;
  }

  ordenPreguntas = mezclar(preguntas.map((_, i) => i)).slice(0, 30);
  simulacroActivo = true;
  primeraPruebaActiva = false;

  botonSimulacro.style.display = "none";
  botonPrimeraPrueba.style.display = "none";
  botonVolver.style.display = "inline-block";
  resultadoFinal.style.display = "none";
  botonTerminar.style.display = "none";

  renderQuiz();
  actualizarContador();
});

botonPrimeraPrueba.addEventListener("click", () => {
  for (let i = 0; i < respuestasUsuario.length; i++) {
    respuestasUsuario[i] = null;
  }

  ordenPreguntas = preguntas
    .map((pregunta, i) => pregunta.grupo === "primera-prueba-25-26" ? i : -1)
    .filter(i => i !== -1);

  simulacroActivo = false;
  primeraPruebaActiva = true;

  botonSimulacro.style.display = "none";
  botonPrimeraPrueba.style.display = "none";
  botonVolver.style.display = "inline-block";
  resultadoFinal.style.display = "none";
  botonTerminar.style.display = "none";

  renderQuiz();
  actualizarContador();
});

botonVolver.addEventListener("click", () => {
  ordenPreguntas = preguntas.map((_, i) => i);
  simulacroActivo = false;
  primeraPruebaActiva = false;

  botonVolver.style.display = "none";
  botonSimulacro.style.display = "inline-block";
  botonPrimeraPrueba.style.display = "inline-block";
  resultadoFinal.style.display = "none";
  botonTerminar.style.display = "none";

  renderQuiz();
  actualizarContador();
});

botonTerminar.addEventListener("click", () => {
  mostrarResultados();
});

botonReiniciar.addEventListener("click", () => {
  for (let i = 0; i < respuestasUsuario.length; i++) {
    respuestasUsuario[i] = null;
  }
  ordenPreguntas = preguntas.map((_, i) => i);
  simulacroActivo = false;
  primeraPruebaActiva = false;
  botonVolver.style.display = "none";
  botonSimulacro.style.display = "inline-block";
  botonPrimeraPrueba.style.display = "inline-block";
  resultadoFinal.style.display = "none";
  botonTerminar.style.display = "none";
  renderQuiz();
  actualizarContador();
  window.scrollTo({ top: 0, behavior: "smooth" });
});

renderQuiz();
actualizarContador();