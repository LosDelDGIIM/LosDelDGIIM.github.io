const preguntas = [
  {
    enunciado: "Una decisión es:",
    opciones: [
      "Una reacción automática ante un problema",
      "La elección entre un conjunto de alternativas",
      "Una acción improvisada sin análisis previo",
      "Una predicción del entorno"
    ],
    correcta: 1,
    explicacion: "Diapositiva 3 del Tema 3."
  },
  {
    enunciado: "En el modelo de resolución de problemas, la primera fase es:",
    opciones: [
      "Aplicar la decisión",
      "Seleccionar la alternativa",
      "Identificar y definir el problema",
      "Evaluación y control"
    ],
    correcta: 2,
    explicacion: "Diapositiva 4 del Tema 3."
  },
  {
    enunciado: "En el proceso de dirección estratégica, el análisis DAFO se sitúa dentro de:",
    opciones: [
      "La ejecución de la estrategia",
      "El control",
      "El análisis estratégico",
      "La gestión de proyectos"
    ],
    correcta: 2,
    explicacion: "Diapositiva 6 del Tema 3."
  },
  {
    enunciado: "Las estrategias o alternativas en un problema de decisión son:",
    opciones: [
      "Variables no controlables",
      "Resultados ya obtenidos",
      "Variables controlables del problema",
      "Probabilidades subjetivas"
    ],
    correcta: 2,
    explicacion: "Diapositiva 8 del Tema 3."
  },
  {
    enunciado: "Los estados de la naturaleza son:",
    opciones: [
      "Decisiones del directivo",
      "Variables controlables",
      "Situaciones del entorno no controlables",
      "Objetivos empresariales"
    ],
    correcta: 2,
    explicacion: "Diapositiva 8 del Tema 3."
  },
  {
    enunciado: "En la matriz de decisión, el desenlace o resultado esperado se refiere a:",
    opciones: [
      "El resultado asociado a cada alternativa dado un estado de la naturaleza",
      "La probabilidad subjetiva del decisor",
      "El conjunto de alternativas disponibles",
      "La duración total del proyecto"
    ],
    correcta: 0,
    explicacion: "Diapositiva 9 del Tema 3."
  },
  {
    enunciado: "En una situación de certeza:",
    opciones: [
      "No se conoce el estado de la naturaleza",
      "Se conocen las probabilidades, pero no el estado",
      "No se conocen ni estado ni probabilidades",
      "El decisor conoce el estado de la naturaleza que se va a dar"
    ],
    correcta: 3,
    explicacion: "Diapositiva 12 del Tema 3."
  },
  {
    enunciado: "En una situación de riesgo:",
    opciones: [
      "El decisor conoce con seguridad qué ocurrirá",
      "El decisor desconoce el estado de la naturaleza, pero puede estimar su predicción",
      "No existe información alguna sobre el entorno",
      "Solo hay una alternativa posible"
    ],
    correcta: 1,
    explicacion: "Diapositiva 12 del Tema 3."
  },
  {
    enunciado: "En una situación de incertidumbre:",
    opciones: [
      "El decisor conoce los resultados exactos",
      "Se conocen las probabilidades de ocurrencia",
      "Ni siquiera se conoce la probabilidad de ocurrencia de los estados de la naturaleza",
      "La mejor alternativa es siempre evidente"
    ],
    correcta: 2,
    explicacion: "Diapositiva 12 del Tema 3."
  },
  {
    enunciado: "En situación de riesgo, las alternativas se valoran normalmente con:",
    opciones: [
      "El criterio de Savage",
      "El valor monetario esperado",
      "El criterio maximin",
      "El criterio de Gantt"
    ],
    correcta: 1,
    explicacion: "Diapositiva 13 del Tema 3."
  },
  {
    enunciado: "La expresión del valor monetario esperado consiste, básicamente, en:",
    opciones: [
      "Sumar los mejores resultados posibles",
      "Multiplicar cada resultado por su probabilidad y sumar",
      "Dividir cada resultado entre su probabilidad",
      "Restar al máximo el mínimo resultado"
    ],
    correcta: 1,
    explicacion: "Diapositiva 13 del Tema 3."
  },
  {
    enunciado: "En el siguiente ejemplo, la alternativa con mayor VME es (en u.m.):",
    imagen: "assets/matriz-agricultor.png",
    opciones: [
      "Patatas",
      "Remolacha",
      "Trigo",
      "Las tres tienen el mismo VME"
    ],
    correcta: 2,
    explicacion: "Diapositiva 14 del Tema 3. Denotando por VME_T al VME del trigo, y VME_P y VME_R a los VME de patata y remolacha, respectivamente, es claro que VME_T > VME_P > VME_R. A modo de ejemplo se calcula VME_T = 250 * 0,3 + 290 * 0,5 + 200 * 0,2."
  },
  {
    enunciado: "El criterio de Laplace parte de la idea de:",
    opciones: [
      "Elegir siempre el peor resultado posible",
      "Suponer equiprobabilidad entre estados de la naturaleza",
      "Ignorar todos los resultados negativos",
      "Trabajar solo con costes de oportunidad"
    ],
    correcta: 1,
    explicacion: "Diapositiva 16 del Tema 3."
  },
  {
    enunciado: "El criterio de Hurwicz:",
    opciones: [
      "Transforma la matriz en costes de oportunidad",
      "Utiliza exclusivamente probabilidades objetivas",
      "Permite fijar un grado de optimismo o pesimismo",
      "Solo sirve en situaciones de certeza"
    ],
    correcta: 2,
    explicacion: "Diapositiva 17 del Tema 3."
  },
  {
    enunciado: "El criterio de Savage sustituye la matriz inicial por una matriz de:",
    opciones: [
      "Probabilidades acumuladas",
      "Costes de oportunidad",
      "Medias aritméticas",
      "Restricciones lineales"
    ],
    correcta: 1,
    explicacion: "Diapositiva 17 del Tema 3."
  },
  {
    enunciado: "Los árboles de decisión se presentan en el tema como:",
    opciones: [
      "Métodos contables para calcular costes",
      "Modelos predictivos para clasificar una población segmentada",
      "Técnicas de marketing digital",
      "Instrumentos jurídicos de protección industrial"
    ],
    correcta: 1,
    explicacion: "Diapositiva 19 del Tema 3."
  },
  {
    enunciado: "En los árboles de decisión, la variable de interés actúa como:",
    opciones: [
      "Variable independiente",
      "Variable dependiente",
      "Restricción",
      "Coste hundido"
    ],
    correcta: 1,
    explicacion: "Diapositiva 19 del Tema 3."
  },
  {
    enunciado: "En los árboles de decisión, las variables explicativas se analizan:",
    opciones: [
      "Todas simultáneamente desde el principio",
      "Una a una, empezando por la más discriminante",
      "Solo al final del proceso",
      "Únicamente si son cualitativas"
    ],
    correcta: 1,
    explicacion: "Diapositiva 20 del Tema 3."
  },
  {
    enunciado: "¿Cuál de los siguientes aparece en el tema como método estadístico de decisión aplicado a la empresa?",
    opciones: [
      "Programación lineal",
      "Análisis sintáctico",
      "Amortización decreciente",
      "Matriz BCG"
    ],
    correcta: 0,
    explicacion: "Diapositiva 24 del Tema 3."
  },
  {
    enunciado: "En programación lineal, se busca:",
    opciones: [
      "Clasificar datos en segmentos",
      "Optimizar una función objetivo sujeta a restricciones lineales",
      "Patentar una invención",
      "Calcular derechos de autor"
    ],
    correcta: 1,
    explicacion: "Diapositiva 25 del Tema 3."
  },
  {
    enunciado: "En el problema de la mochila, el objetivo es:",
    opciones: [
      "Minimizar la distancia entre dos vértices",
      "Maximizar la utilidad sin sobrepasar el peso máximo soportado",
      "Asignar vendedores a clientes",
      "Calcular la duración optimista de un proyecto"
    ],
    correcta: 1,
    explicacion: "Diapositiva 28 del Tema 3."
  },
  {
    enunciado: "El problema del transporte es:",
    opciones: [
      "Un tipo particular de programación lineal",
      "Un caso de derecho mercantil",
      "Un criterio de incertidumbre",
      "Una técnica exclusiva de marketing"
    ],
    correcta: 0,
    explicacion: "Diapositiva 30 del Tema 3."
  },
  {
    enunciado: "En el problema del transporte, en general hay solución factible si y solo si:",
    opciones: [
      "La oferta es superior a la demanda",
      "La oferta es inferior a la demanda",
      "La oferta y la demanda son siempre iguales",
      "La demanda es nula"
    ],
    correcta: 0,
    explicacion: "Diapositiva 30 del Tema 3. Según la diapositiva sería correcta la opción 'la oferta es inferior a la demanda' pero es una errata."
  },
  {
    enunciado: "En el problema del transporte, SAS puede resolverlo mediante:",
    opciones: [
      "PROC TRANS o procedimiento de programación lineal LP",
      "PROC GANTT exclusivamente",
      "El criterio de Savage",
      "La matriz de costes de oportunidad"
    ],
    correcta: 0,
    explicacion: "Diapositiva 30 del Tema 3."
  },
  {
    enunciado: "El problema de la asignación lineal consiste en:",
    opciones: [
      "Repartir impuestos entre territorios",
      "Asignar recursos a la realización de tareas",
      "Predecir la demanda futura",
      "Elegir una única estrategia bajo riesgo"
    ],
    correcta: 1,
    explicacion: "Diapositiva 33 del Tema 3."
  },
  {
    enunciado: "En el problema del camino mínimo, los dos nodos especiales se denominan:",
    opciones: [
      "Raíz y hoja",
      "Fuente y sumidero",
      "Origen y destino",
      "Oferta y demanda"
    ],
    correcta: 2,
    explicacion: "Diapositiva 36 del Tema 3."
  },
  {
    enunciado: "El fundamento teórico del problema del camino mínimo lo proporciona:",
    opciones: [
      "El principio de optimalidad de Bellman",
      "El criterio de Laplace",
      "La ley de oferta y demanda",
      "El método de amortización lineal"
    ],
    correcta: 0,
    explicacion: "Diapositiva 37 del Tema 3."
  },
  {
    enunciado: "El problema del camino mínimo puede resolverse, entre otros, mediante:",
    opciones: [
      "Ford-Fulkerson",
      "Dijkstra",
      "Wald",
      "Hurwicz"
    ],
    correcta: 1,
    explicacion: "Diapositiva 37 del Tema 3."
  },
  {
    enunciado: "En el problema del flujo máximo, los nodos que no son fuente ni destino se llaman:",
    opciones: [
      "Nodos rígidos",
      "Nodos de trasbordo",
      "Nodos de decisión",
      "Nudos críticos"
    ],
    correcta: 1,
    explicacion: "Diapositiva 40 del Tema 3."
  },
  {
    enunciado: "En el problema del flujo máximo, el objetivo es:",
    opciones: [
      "Minimizar el número de nodos",
      "Maximizar la cantidad total de flujo de la fuente al destino",
      "Minimizar el coste de oportunidad",
      "Clasificar observaciones en segmentos"
    ],
    correcta: 1,
    explicacion: "Diapositiva 40 del Tema 3."
  },
  {
    enunciado: "El método PERT fue utilizado inicialmente por:",
    opciones: [
      "La empresa Dupont",
      "La OCDE",
      "El ejército de los Estados Unidos",
      "La Comisión Europea"
    ],
    correcta: 2,
    explicacion: "Diapositiva 44 del Tema 3."
  },
  {
    enunciado: "El método CPM fue creado por:",
    opciones: [
      "Pixar",
      "Toyota",
      "Dupont",
      "Nestlé"
    ],
    correcta: 2,
    explicacion: "Diapositiva 44 del Tema 3."
  },
  {
    enunciado: "En gestión de proyectos, el gráfico de Gantt se caracteriza por:",
    opciones: [
      "Ser una técnica basada en utilidad esperada",
      "Representar en horizontal el tiempo y en vertical las tareas",
      "Servir solo para problemas de transporte",
      "Calcular el flujo máximo de una red"
    ],
    correcta: 1,
    explicacion: "Diapositiva 45 del Tema 3."
  },
  {
    enunciado: "La idea fundamental del método PERT es:",
    opciones: [
      "La interrelación temporal entre las tareas, actividades o fases de un proyecto complejo",
      "La comparación de patentes y modelos de utilidad",
      "La maximización de la utilidad de una mochila",
      "La elección de la alternativa con mayor VME"
    ],
    correcta: 0,
    explicacion: "Diapositiva 46 del Tema 3."
  },
  {
    enunciado: "En la base matemática del PERT, un grafo es:",
    opciones: [
      "Un conjunto de elementos ligados por relaciones orientadas, con nudos o vértices y arcos o flechas",
      "Una tabla de probabilidades de los estados de la naturaleza",
      "Una función objetivo con restricciones lineales",
      "Un conjunto de activos y pasivos"
    ],
    correcta: 0,
    explicacion: "Diapositiva 47 del Tema 3."
  },
  {
    enunciado: "Una característica del grafo PERT es que:",
    opciones: [
      "Debe ser un grafo sin circuitos",
      "Debe tener infinitos vértices",
      "Debe incluir dos actividades con el mismo par de números",
      "Debe ser necesariamente no conexo"
    ],
    correcta: 0,
    explicacion: "Diapositiva 48 del Tema 3."
  },
  {
    enunciado: "En el grafo PERT, las actividades o fases se representan como:",
    opciones: [
      "Nudos iniciales",
      "Arcos o flechas",
      "Probabilidades",
      "Estados de la naturaleza"
    ],
    correcta: 1,
    explicacion: "Diapositiva 52 del Tema 3."
  },
  {
    enunciado: "En PERT, la duración total de un proyecto:",
    opciones: [
      "Es siempre la suma simple de todas las actividades",
      "No es la mera suma de actividades, porque algunas pueden ejecutarse simultáneamente",
      "Depende solo del número de vértices",
      "Se calcula siempre con el criterio de Wald"
    ],
    correcta: 1,
    explicacion: "Diapositiva 53 del Tema 3."
  },
  {
    enunciado: "En la primera fase del cálculo del tiempo en PERT se calculan:",
    opciones: [
      "Las fechas más tempranas o earliest",
      "Los costes de oportunidad",
      "Las marcas registradas",
      "Las probabilidades de cada cultivo"
    ],
    correcta: 0,
    explicacion: "Diapositiva 55 del Tema 3."
  },
  {
    enunciado: "En la tercera fase del cálculo del tiempo en PERT se identifica:",
    opciones: [
      "El camino crítico",
      "La patente comunitaria",
      "El valor monetario esperado",
      "La solución factible del transporte"
    ],
    correcta: 0,
    explicacion: "Diapositiva 57 del Tema 3."
  },
  {
    enunciado: "Cuando no se dispone de duración cierta para las actividades, en PERT se suele usar:",
    opciones: [
      "La función beta simplificada",
      "El criterio optimista de Savage",
      "La matriz DAFO",
      "El gráfico de dispersión"
    ],
    correcta: 0,
    explicacion: "Diapositiva 63 del Tema 3."
  },
  {
    enunciado: "En la función beta del PERT, la duración más probable se pondera:",
    opciones: [
      "Igual que la optimista y la pesimista",
      "Dos veces más que la optimista",
      "Cuatro veces más que la optimista y la pesimista",
      "Nunca se pondera"
    ],
    correcta: 2,
    explicacion: "Diapositiva 65 del Tema 3."
  },
  {
    enunciado: "PERT-Coste añade al PERT-Tiempo:",
    opciones: [
      "La inclusión explícita de los costes",
      "La eliminación del camino crítico",
      "La sustitución de los arcos por marcas",
      "La transformación de riesgo en incertidumbre"
    ],
    correcta: 0,
    explicacion: "Diapositiva 66 del Tema 3."
  },
  {
    enunciado: "Según lo que se ha visto en teoría, la ciencia es principalmente:",
    opciones: [
      "Un conjunto ordenado de conocimientos estructurados sistemáticamente",
      "Un producto comercializable",
      "Una técnica de marketing",
      "Un derecho de propiedad industrial"
    ],
    correcta: 0,
    explicacion: "Diapositiva 3 del Tema 4."
  },
  {
    enunciado: "Una característica de la ciencia, según las diapositivas, es que:",
    opciones: [
      "Surge de la investigación básica",
      "Tiene aplicación comercial inmediata siempre",
      "Es conocimiento tácito",
      "No genera principios ni leyes"
    ],
    correcta: 0,
    explicacion: "Diapositiva 6 del Tema 4."
  },
  {
    enunciado: "La tecnología se define como:",
    opciones: [
      "Un producto físico concreto",
      "El conjunto de conocimientos técnicos, científicamente ordenados, que permiten diseñar y crear bienes y servicios",
      "Solo maquinaria industrial",
      "Únicamente software"
    ],
    correcta: 1,
    explicacion: "Diapositiva 7 del Tema 4."
  },
  {
    enunciado: "Una idea importante vista en teoría es que:",
    opciones: [
      "Tecnología y producto son exactamente lo mismo",
      "Toda tecnología da lugar a un único producto",
      "El producto es el mensajero de la tecnología",
      "La tecnología solo existe cuando se vende"
    ],
    correcta: 2,
    explicacion: "Diapositiva 12 del Tema 4."
  },
  {
    enunciado: "Para que una tecnología tenga éxito en un contexto social deben darse, entre otras, estas condiciones:",
    opciones: [
      "Necesidad social, recursos sociales y grupos dispuestos a alentar la creatividad",
      "Monopolio legal, subvención pública y publicidad masiva",
      "Solo una necesidad técnica",
      "Únicamente abundancia de capital"
    ],
    correcta: 0,
    explicacion: "Diapositiva 13 del Tema 4."
  },
  {
    enunciado: "En la comparación ciencia-tecnología, la motivación de la ciencia es:",
    opciones: [
      "La satisfacción de necesidades y deseos",
      "El ansia de conocimientos y comprensión racional del mundo",
      "La obtención de patentes",
      "La diferenciación comercial"
    ],
    correcta: 1,
    explicacion: "Diapositiva 14 del Tema 4."
  },
  {
    enunciado: "En la comparación ciencia-tecnología, el producto propio de la tecnología es:",
    opciones: [
      "Publicaciones científicas",
      "Conocimientos explícitos",
      "Bienes, servicios, métodos y procesos",
      "Leyes generales"
    ],
    correcta: 2,
    explicacion: "Diapositiva 14 del Tema 4."
  },
  {
    enunciado: "La etapa del ciclo de vida tecnológico en la que el desarrollo es incipiente y hay que invertir mucho en promoción es:",
    opciones: [
      "Madurez",
      "Crecimiento",
      "Emergencia",
      "Saturación"
    ],
    correcta: 2,
    explicacion: "Diapositiva 15 del Tema 4."
  },
  {
    enunciado: "La etapa del ciclo de vida tecnológico en la que la tecnología se estabiliza y suele ser el periodo más rentable es:",
    opciones: [
      "Emergencia",
      "Madurez",
      "Saturación",
      "Declive inicial de mercado"
    ],
    correcta: 1,
    explicacion: "Diapositiva 19 del Tema 4."
  },
  {
    enunciado: "En saturación o declive:",
    opciones: [
      "Los beneficios crecen y los costes bajan",
      "La tecnología empieza a ser conocida",
      "La tecnología se vuelve obsoleta, los costes crecen y los beneficios disminuyen",
      "Se convierte en tecnología emergente"
    ],
    correcta: 2,
    explicacion: "Diapositiva 20 del Tema 4."
  },
  {
    enunciado: "Las tecnologías emergentes:",
    opciones: [
      "Son siempre rentables de inmediato",
      "Son inmaduras, implican riesgo y pueden convertirse en clave en el futuro",
      "No tienen relación con la innovación",
      "Equivalen a tecnologías básicas"
    ],
    correcta: 1,
    explicacion: "Diapositiva 22 del Tema 4."
  },
  {
    enunciado: "Según las diapositivas, los coches de hidrógeno se consideran:",
    opciones: [
      "Tecnología básica ya obsoleta",
      "Una promesa dentro del sector del automóvil vinculada a tecnologías emergentes",
      "Una forma de copyright",
      "Un ejemplo de modelo de utilidad"
    ],
    correcta: 1,
    explicacion: "Diapositiva 23 del Tema 4."
  },
  {
    enunciado: "Las tecnologías clave son las que:",
    opciones: [
      "Ya no sirven para competir",
      "Solo existen en laboratorios",
      "Otorgan posición en el mercado y ventaja competitiva",
      "Carecen de utilidad empresarial"
    ],
    correcta: 2,
    explicacion: "Diapositiva 24 del Tema 4."
  },
  {
    enunciado: "Las tecnologías básicas son aquellas que:",
    opciones: [
      "Otorgan ventaja competitiva decisiva",
      "Son imprescindibles para la actividad principal, pero no suponen ventaja competitiva",
      "Están en fase inmadura y de alto riesgo",
      "Solo usan las startups"
    ],
    correcta: 1,
    explicacion: "Diapositiva 25 del Tema 4."
  },
  {
    enunciado: "Según Schumpeter, invenciones e innovaciones son clave para:",
    opciones: [
      "El crecimiento económico",
      "La reducción de toda competencia",
      "La eliminación del emprendimiento",
      "La obsolescencia tecnológica"
    ],
    correcta: 0,
    explicacion: "Diapositiva 29 del Tema 4."
  },
  {
    enunciado: "Según el objeto, la innovación puede ser:",
    opciones: [
      "Táctica o estratégica",
      "Pública o privada",
      "De producto o de proceso",
      "Básica o aplicada"
    ],
    correcta: 2,
    explicacion: "Diapositiva 32 del Tema 4."
  },
  {
    enunciado: "Según su profundidad, la innovación puede ser:",
    opciones: [
      "Radical o incremental",
      "Simple o compuesta",
      "Fija o variable",
      "Jurídica o económica"
    ],
    correcta: 0,
    explicacion: "Diapositiva 32 del Tema 4."
  },
  {
    enunciado: "Innovar, según lo visto en teoría, es:",
    opciones: [
      "Copiar productos existentes",
      "Crear nuevos conocimientos o emplear los existentes para desarrollar nuevos productos, procesos o servicios",
      "Registrar una marca",
      "Vender más que la competencia"
    ],
    correcta: 1,
    explicacion: "Diapositiva 35 del Tema 4."
  },
  {
    enunciado: "En la relación entre ciencia, tecnología e innovación, la ciencia se presenta como:",
    opciones: [
      "El cuerpo teórico que nutre a la innovación y a la tecnología",
      "El output exclusivo de la innovación",
      "Una actividad sin relación con la tecnología",
      "Un mecanismo de protección industrial"
    ],
    correcta: 0,
    explicacion: "Diapositiva 36 del Tema 4."
  },
  {
    enunciado: "Si el espíritu emprendedor surge dentro de otra organización, hablamos de:",
    opciones: [
      "Startup",
      "Spinoff",
      "Franquicia",
      "Joint venture"
    ],
    correcta: 1,
    explicacion: "Diapositiva 38 del Tema 4."
  },
  {
    enunciado: "En las NEBT, si el espíritu emprendedor surge de forma independiente, se generan:",
    opciones: [
      "Spinoffs",
      "Startups",
      "Patentes comunitarias",
      "Business angels"
    ],
    correcta: 1,
    explicacion: "Diapositiva 38 del Tema 4."
  },
  {
    enunciado: "La diferencia principal entre startup y spinoff que subrayan las diapositivas es:",
    opciones: [
      "El tamaño",
      "El origen",
      "El número de empleados",
      "La forma jurídica"
    ],
    correcta: 1,
    explicacion: "Diapositiva 38 del Tema 4."
  },
  {
    enunciado: "Una NEBT se considera como tal cuando, entre otros rasgos:",
    opciones: [
      "Tiene más de 10 años",
      "Su ventaja competitiva viene del tamaño",
      "Tiene menos de 3 años y su ventaja competitiva depende del dominio de la tecnología",
      "Opera solo en mercados totalmente definidos"
    ],
    correcta: 2,
    explicacion: "Diapositiva 39 del Tema 4."
  },
  {
    enunciado: "Según las condiciones generales de las NEBT, estas empresas se relacionan con el sistema económico mediante:",
    opciones: [
      "La transferencia tecnológica",
      "La amortización contable",
      "El análisis DAFO exclusivamente",
      "La financiación bancaria ordinaria únicamente"
    ],
    correcta: 0,
    explicacion: "Diapositiva 39 del Tema 4."
  },
  {
    enunciado: "En la gestión de NEBTs, trabajar con clientes reales que prueban y opinan sobre prototipos implica:",
    opciones: [
      "Feedback iterativo",
      "Secreto industrial obligatorio",
      "Ausencia de incertidumbre",
      "Protección automática mundial"
    ],
    correcta: 0,
    explicacion: "Diapositiva 40 del Tema 4."
  },
  {
    enunciado: "En la gestión de startups, pivotar significa:",
    opciones: [
      "Cambiar el producto de acuerdo con el feedback del cliente",
      "Registrar una patente durante 20 años",
      "Sustituir a todos los proveedores",
      "Acudir directamente a mercados financieros"
    ],
    correcta: 0,
    explicacion: "Diapositiva 41 del Tema 4."
  },
  {
    enunciado: "En el modelo de innovación abierta, las startups funcionan como:",
    opciones: [
      "Base tecnológica externa",
      "Base tecnológica interna",
      "Órganos de administración",
      "Modelos de utilidad"
    ],
    correcta: 0,
    explicacion: "Diapositiva 44 del Tema 4."
  },
  {
    enunciado: "En el modelo de innovación abierta, los aceleradores son:",
    opciones: [
      "Oficinas públicas de patentes",
      "Espacios que conectan NEBT con inversores, asesores y cazatalentos para acelerar el paso a prototipo testable",
      "Laboratorios universitarios cerrados",
      "Mercados secundarios de acciones"
    ],
    correcta: 1,
    explicacion: "Diapositiva 44 del Tema 4."
  },
  {
    enunciado: "En financiación de NEBT, las 3Fs significan:",
    opciones: [
      "Family, friends and fools",
      "Funding, firms and finance",
      "Founders, factories and forecasts",
      "Funds, fees and futures"
    ],
    correcta: 0,
    explicacion: "Diapositiva 47 del Tema 4."
  },
  {
    enunciado: "Un Business Angel se caracteriza por:",
    opciones: [
      "Aportar su propio dinero a empresas no cotizadas promovidas por personas ajenas",
      "Invertir siempre dinero público",
      "Actuar solo en empresas cotizadas maduras",
      "No tomar sus propias decisiones de inversión"
    ],
    correcta: 0,
    explicacion: "Diapositiva 48 del Tema 4."
  },
  {
    enunciado: "El venture capital se define como una actividad de:",
    opciones: [
      "Invertir como accionistas en empresas atractivas con vocación temporal para desinvertir después",
      "Conceder préstamos bancarios ordinarios sin participación",
      "Registrar marcas y nombres comerciales",
      "Proteger información mediante secreto"
    ],
    correcta: 0,
    explicacion: "Diapositiva 49 del Tema 4."
  },
  {
    enunciado: "Una de las barreras para la aparición de NEBT's es:",
    opciones: [
      "La existencia de capital",
      "La ausencia total de tecnología",
      "El exceso de marcas registradas",
      "La obligatoriedad de usar PERT"
    ],
    correcta: 0,
    explicacion: "Diapositiva 51 del Tema 4."
  },
  {
    enunciado: "La protección mediante secreto se basa en:",
    opciones: [
      "El compromiso de no divulgar información por parte de personas relacionadas con la tecnología",
      "La concesión automática de una patente comunitaria",
      "La publicación inmediata de todo el know-how",
      "El registro de una marca comercial"
    ],
    correcta: 0,
    explicacion: "Diapositiva 54 del Tema 4."
  },
  {
    enunciado: "El conocimiento confidencial de tipo tecnológico al que pueden acceder profesionales se denomina:",
    opciones: [
      "Know-how",
      "VME",
      "Gantt",
      "Crowdfunding"
    ],
    correcta: 0,
    explicacion: "Diapositiva 55 del Tema 4."
  },
  {
    enunciado: "Los derechos conexos al copyright pertenecen, entre otros, a:",
    opciones: [
      "Artistas, productores de discos u organizaciones de difusión",
      "Solo empresas farmacéuticas",
      "Solo titulares de patentes industriales",
      "Únicamente bancos comerciales"
    ],
    correcta: 0,
    explicacion: "Diapositiva 56 del Tema 4."
  },
  {
    enunciado: "Los derechos de autor protegen:",
    opciones: [
      "Exclusivamente patentes químicas",
      "Obras artísticas, literarias, películas y programas de ordenador, entre otros",
      "Únicamente marcas comerciales",
      "Solo diseños industriales"
    ],
    correcta: 1,
    explicacion: "Diapositiva 57 del Tema 4."
  },
  {
    enunciado: "La propiedad industrial protege:",
    opciones: [
      "Solo artículos científicos",
      "La actividad innovadora y mercantil mediante títulos como patentes, modelos y marcas",
      "Únicamente obras audiovisuales",
      "Solo secretos empresariales no registrados"
    ],
    correcta: 1,
    explicacion: "Diapositiva 58 del Tema 4."
  },
  {
    enunciado: "Las patentes de invención protegen:",
    opciones: [
      "Descubrimientos científicos sin aplicación",
      "Inventos, pero no descubrimientos científicos",
      "Cualquier idea sin requisitos",
      "Solo nombres comerciales"
    ],
    correcta: 1,
    explicacion: "Diapositiva 59 del Tema 4."
  },
  {
    enunciado: "Entre los requisitos para patentar que aparecen en el tema están:",
    opciones: [
      "Novedad y aplicación industrial",
      "Fama del inventor y tamaño de la empresa",
      "Antigüedad de la organización",
      "Volumen de ventas"
    ],
    correcta: 0,
    explicacion: "Diapositiva 60 del Tema 4."
  },
  {
    enunciado: "Las marcas registradas protegen principalmente:",
    opciones: [
      "Procesos industriales secretos",
      "Palabras, frases y símbolos que sirvan para registrar productos o servicios",
      "Artículos científicos",
      "Algoritmos matemáticos"
    ],
    correcta: 1,
    explicacion: "Diapositiva 61 del Tema 4."
  },
  {
    enunciado: "En el sistema español de patentes, una patente dura:",
    opciones: [
      "20 años improrrogables",
      "10 años improrrogables",
      "5 años renovables indefinidamente",
      "Toda la vida del inventor"
    ],
    correcta: 0,
    explicacion: "Diapositiva 63 del Tema 4."
  },
  {
    enunciado: "Si una patente no es explotada:",
    opciones: [
      "Podrá caducar",
      "Se convierte automáticamente en marca",
      "Se prorroga indefinidamente",
      "Pasa a ser copyright"
    ],
    correcta: 0,
    explicacion: "Diapositiva 64 del Tema 4."
  },
  {
    enunciado: "Desde el punto de vista de la gestión de la propiedad intelectual, la actividad de I+D susceptible de protección puede realizarse:",
    opciones: [
      "Solo en solitario",
      "Solo mediante compra de licencias",
      "En solitario, bajo contrato o cooperativamente",
      "Únicamente dentro de la universidad"
    ],
    correcta: 2,
    explicacion: "Diapositiva 66 del Tema 4."
  },
  {
    enunciado: "(Segunda Prueba 25-26) En el proceso de dirección estratégica, la fase de formulación de estrategias depende críticamente de...",
    opciones: [
      "La disponibilidad de recursos financieros",
      "La coherencia entre análisis interno y externo",
      "La estructura organizativa",
      "La cultura corporativa"
    ],
    correcta: 1,
    explicacion: "Diapositiva 6 Tema 3.",
    grupo: "segunda-prueba-25-26"
  },
  {
    enunciado: "(Segunda Prueba 25-26) En un problema de decisión, la interacción entre alternativas y estados de la naturaleza se representa mediante...",
    opciones: [
      "Un árbol de probabilidad",
      "Una matriz de decisión",
      "Un gráfico DAFO",
      "Un análisis de sensibilidad"
    ],
    correcta: 1,
    explicacion: "Diapositiva 10 Tema 3.",
    grupo: "segunda-prueba-25-26"
  },
  {
    enunciado: "(Segunda Prueba 25-26) El criterio de Hurwicz se caracteriza por...",
    opciones: [
      "Utilizar probabilidades equiprobables",
      "Seleccionar el máximo de los mínimos",
      "Combinar optimismo y pesimismo mediante un coeficiente",
      "Basarse en costes de oportunidad"
    ],
    correcta: 2,
    explicacion: "Diapositiva 17 Tema 3.",
    grupo: "segunda-prueba-25-26"
  },
  {
    enunciado: "(Segunda Prueba 25-26) El criterio de Savage es especialmente útil cuando...",
    opciones: [
      "Se conocen las probabilidades",
      "Se desconoce toda probabilidad y se quiere minimizar el arrepentimiento",
      "Se busca el mejor resultado posible",
      "Se quiere maximizar el valor esperado"
    ],
    correcta: 1,
    explicacion: "Diapositiva 17 Tema 3. En la diapositiva se dice que se usa una matriz de costes de oportunidad, lo que se entiende equivalente a minimizar el arrepentimiento.",
    grupo: "segunda-prueba-25-26"
  },
  {
    enunciado: "(Segunda Prueba 25-26) En decisiones secuenciales, la regla fundamental para resolver un árbol de decisión es...",
    opciones: [
      "Evaluar de izquierda a derecha",
      "Evaluar de derecha a izquierda (rollback)",
      "Evaluar solo los nodos de azar",
      "Evaluar solo los nodos de decisión"
    ],
    correcta: 1,
    explicacion: "Diapositiva 20 Tema 3. No aparece explícitamente.",
    grupo: "segunda-prueba-25-26"
  },
  {
    enunciado: "(Segunda Prueba 25-26) En programación lineal, una solución factible es aquella que...",
    opciones: [
      "Maximiza la función objetivo",
      "Satisface todas las restricciones",
      "Minimiza los costes",
      "Tiene todas las variables en cero"
    ],
    correcta: 1,
    explicacion: "Diapositiva 25 Tema 3.",
    grupo: "segunda-prueba-25-26"
  },
  {
    enunciado: "(Segunda Prueba 25-26) El problema del transporte se considera balanceado cuando...",
    opciones: [
      "La oferta supera la demanda",
      "La demanda supera la oferta",
      "Oferta y demanda son iguales",
      "No existen costes negativos"
    ],
    correcta: 2,
    explicacion: "Diapositiva 30 Tema 3. No aparece explícitamente. Además, hay que cambiar 'oferta' por 'demanda' en el tercer punto.",
    grupo: "segunda-prueba-25-26"
  },
  {
    enunciado: "(Segunda Prueba 25-26) El problema del flujo máximo se basa en...",
    opciones: [
      "El algoritmo de Dijkstra",
      "El algoritmo Ford-Fulkerson",
      "El método simplex",
      "El criterio de Laplace"
    ],
    correcta: 1,
    explicacion: "Diapositiva 40 Tema 3.",
    grupo: "segunda-prueba-25-26"
  },
  {
    enunciado: "(Segunda Prueba 25-26) En PERT, la ausencia de circuitos en el grafo se debe a...",
    opciones: [
      "La necesidad de minimizar costes",
      "El principio de causalidad temporal",
      "La optimización de recursos",
      "La reducción de nodos críticos"
    ],
    correcta: 1,
    explicacion: "Diapositiva 48 Tema 3.",
    grupo: "segunda-prueba-25-26"
  },
  {
    enunciado: "(Segunda Prueba 25-26) El camino crítico determina...",
    opciones: [
      "La duración mínima del proyecto",
      "La duración máxima del proyecto",
      "Las actividades con mayor holgura",
      "Las actividades que pueden retrasarse sin afectar al proyecto"
    ],
    correcta: 0,
    explicacion: "Diapositivas 53-55 del Tema 3. La duración total del proyecto es el tiempo entre el suceso inicial y el final, no la suma de todas las actividades, porque algunas pueden ejecutarse simultáneamente. El camino crítico es el camino de mayor duración entre los nudos inicial y final, y por eso determina la fecha de terminación del proyecto.",
    grupo: "segunda-prueba-25-26"
  },
  {
    enunciado: "(Segunda Prueba 25-26) Una tecnología emergente puede fracasar si...",
    opciones: [
      "No existe una necesidad social clara",
      "Tiene un alto potencial",
      "Es apoyada por grupos creativos",
      "Recibe inversión temprana"
    ],
    correcta: 0,
    explicacion: "Diapositiva 13 Tema 4.",
    grupo: "segunda-prueba-25-26"
  },
  {
    enunciado: "(Segunda Prueba 25-26) La diferencia esencial entre tecnología y producto es que...",
    opciones: [
      "La tecnología es tangible y el producto no",
      "El producto es el vehículo de la tecnología",
      "La tecnología es comercial y el producto no",
      "El producto es conocimiento teórico"
    ],
    correcta: 1,
    explicacion: "Diapositiva 12 Tema 4. Cambia 'vehículo' por 'mensajero'.",
    grupo: "segunda-prueba-25-26"
  },
  {
    enunciado: "(Segunda Prueba 25-26) Una tecnología clave se caracteriza por...",
    opciones: [
      "Ser imprescindible pero no diferenciadora",
      "Ser la base de la ventaja competitiva",
      "Estar en declive",
      "Ser experimental"
    ],
    correcta: 1,
    explicacion: "Diapositiva 24 Tema 4.",
    grupo: "segunda-prueba-25-26"
  },
  {
    enunciado: "(Segunda Prueba 25-26) Una tecnología básica suele haber sido...",
    opciones: [
      "Una tecnología clave en el pasado",
      "Una tecnología emergente",
      "Una tecnología obsoleta",
      "Una tecnología radical"
    ],
    correcta: 0,
    explicacion: "Diapositiva 25 Tema 4.",
    grupo: "segunda-prueba-25-26"
  },
  {
    enunciado: "(Segunda Prueba 25-26) La innovación radical suele asociarse a...",
    opciones: [
      "Cambios incrementales",
      "Nuevas trayectorias tecnológicas",
      "Mejoras menores",
      "Optimización de procesos existentes"
    ],
    correcta: 1,
    explicacion: "Diapositiva 32 Tema 4.",
    grupo: "segunda-prueba-25-26"
  },
  {
    enunciado: "(Segunda Prueba 25-26) La innovación incremental es más frecuente en...",
    opciones: [
      "Startups",
      "Grandes empresas consolidadas",
      "Spinoffs universitarias",
      "Empresas de base tecnológica en fase semilla"
    ],
    correcta: 1,
    explicacion: "Diapositiva 42 Tema 4.",
    grupo: "segunda-prueba-25-26"
  },
  {
    enunciado: "(Segunda Prueba 25-26) Según Schumpeter, el motor del desarrollo económico es...",
    opciones: [
      "El capital financiero",
      "La competencia perfecta",
      "El empresario innovador",
      "El Estado"
    ],
    correcta: 2,
    explicacion: "Diapositivas 29 y 31 Tema 4.",
    grupo: "segunda-prueba-25-26"
  },
  {
    enunciado: "(Segunda Prueba 25-26) Una startup se diferencia de una spinoff principalmente por...",
    opciones: [
      "Su tamaño",
      "Su origen organizativo",
      "Su nivel de riesgo",
      "Su estructura de propiedad"
    ],
    correcta: 1,
    explicacion: "Diapositiva 38 Tema 4.",
    grupo: "segunda-prueba-25-26"
  },
  {
    enunciado: "(Segunda Prueba 25-26) Las NEBT suelen construir capacidades innovadoras mediante...",
    opciones: [
      "Integración vertical",
      "Vínculos externos con clientes y proveedores",
      "Departamentos internos de I+D masivos",
      "Fusiones y adquisiciones"
    ],
    correcta: 1,
    explicacion: "Diapositiva 42 Tema 4.",
    grupo: "segunda-prueba-25-26"
  },
  {
    enunciado: "(Segunda Prueba 25-26) En innovación abierta, las startups actúan como...",
    opciones: [
      "Competidores directos",
      "Proveedores de tecnología externa",
      "Sustitutos de la I+D interna",
      "Barreras de entrada"
    ],
    correcta: 1,
    explicacion: "Diapositiva 44 Tema 4.",
    grupo: "segunda-prueba-25-26"
  },
  {
    enunciado: "(Segunda Prueba 25-26) El venture capital busca...",
    opciones: [
      "Permanecer indefinidamente en la empresa",
      "Salir con plusvalías en un horizonte temporal definido",
      "Controlar la gestión operativa",
      "Evitar riesgos altos"
    ],
    correcta: 1,
    explicacion: "Diapositiva 49 Tema 4.",
    grupo: "segunda-prueba-25-26"
  },
  {
    enunciado: "(Segunda Prueba 25-26) Los business angels se diferencian del venture capital en que...",
    opciones: [
      "Invierten cantidades mayores",
      "Invierten dinero propio",
      "Exigen control total",
      "Solo invierten en empresas maduras"
    ],
    correcta: 1,
    explicacion: "Diapositiva 48 Tema 4. Las 'entidades de Capital Riesgo' mencionadas son las entidades del 'venture capital'.",
    grupo: "segunda-prueba-25-26"
  },
  {
    enunciado: "(Segunda Prueba 25-26) El método Lean Startup considera que el principal riesgo es...",
    opciones: [
      "La falta de financiación",
      "Construir un producto que nadie quiere",
      "La competencia",
      "La falta de marketing"
    ],
    correcta: 1,
    explicacion: "Diapositiva 41 Tema 4. No aparece explícitamente.",
    grupo: "segunda-prueba-25-26"
  },
  {
    enunciado: "(Segunda Prueba 25-26) El producto mínimo viable (MVP) permite...",
    opciones: [
      "Lanzar un producto perfecto",
      "Validar hipótesis con el menor coste posible",
      "Evitar el contacto con clientes",
      "Reducir la innovación"
    ],
    correcta: 1,
    explicacion: "Diapositiva 41 Tema 4.",
    grupo: "segunda-prueba-25-26"
  },
  {
    enunciado: "(Segunda Prueba 25-26) Pivotar implica...",
    opciones: [
      "Cambiar radicalmente el modelo de negocio sin evidencia",
      "Ajustar la estrategia basándose en aprendizaje validado",
      "Abandonar el proyecto",
      "Reducir costes operativos"
    ],
    correcta: 1,
    explicacion: "Diapositiva 41 Tema 4.",
    grupo: "segunda-prueba-25-26"
  },
  {
    enunciado: "(Segunda Prueba 25-26) En el modelo de innovación abierta, las spinoffs pueden actuar como...",
    opciones: [
      "Competidores externos",
      "Vehículos de transferencia tecnológica",
      "Barreras de entrada",
      "Sustitutos del capital riesgo"
    ],
    correcta: 1,
    explicacion: "Diapositivas 43 y 44 Tema 4.",
    grupo: "segunda-prueba-25-26"
  },
  {
    enunciado: "(Segunda Prueba 25-26) Las grandes empresas suelen tener dificultades para innovar radicalmente porque...",
    opciones: [
      "Carecen de recursos",
      "Tienen intereses creados en trayectorias tecnológicas existentes",
      "No tienen acceso a mercados",
      "No pueden contratar talento"
    ],
    correcta: 1,
    explicacion: "Diapositiva 42 Tema 4.",
    grupo: "segunda-prueba-25-26"
  },
  {
    enunciado: "(Segunda Prueba 25-26) Las NEBT suelen centrarse en...",
    opciones: [
      "Mercados masivos",
      "Nichos tecnológicos especializados",
      "Productos de bajo valor añadido",
      "Mercados maduros"
    ],
    correcta: 1,
    explicacion: "Diapositiva 42 Tema 4.",
    grupo: "segunda-prueba-25-26"
  },
  {
    enunciado: "(Segunda Prueba 25-26) La relación entre ciencia y tecnología es...",
    opciones: [
      "Unidireccional: la ciencia crea tecnología",
      "Bidireccional: ambas se retroalimentan",
      "Independiente",
      "Competitiva"
    ],
    correcta: 1,
    explicacion: "Diapositiva 36 Tema 4.",
    grupo: "segunda-prueba-25-26"
  },
  {
    enunciado: "(Segunda Prueba 25-26) La innovación es...",
    opciones: [
      "La creación de conocimiento científico",
      "La aplicación exitosa de ideas en el mercado",
      "La invención sin aplicación",
      "La mejora de procesos internos sin impacto externo"
    ],
    correcta: 1,
    explicacion: "Diapositiva 27 Tema 4.",
    grupo: "segunda-prueba-25-26"
  },
];

const quiz = document.getElementById("quiz");

// Estado de cada pregunta: null = no respondida, número = opción elegida
const respuestasUsuario = Array(preguntas.length).fill(null);

// Orden visible actual de las preguntas
let ordenPreguntas = preguntas.map((_, i) => i);

// Estado de simulacro
let simulacroActivo = false;
let segundaPruebaActiva = false;
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

const botonSegundaPrueba = document.createElement("button");
botonSegundaPrueba.textContent = "Segunda Prueba 25-26";
botonSegundaPrueba.style.marginRight = "10px";

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
barra.appendChild(botonSegundaPrueba);
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

    if (pregunta.imagen) {
      const imagen = document.createElement("img");
      imagen.src = pregunta.imagen;
      imagen.alt = "Imagen para la pregunta";
      imagen.className = "imagen-pregunta";
      contenedor.appendChild(imagen);
    }

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
  segundaPruebaActiva = false;

  botonSimulacro.style.display = "none";
  botonSegundaPrueba.style.display = "none";
  botonVolver.style.display = "inline-block";
  resultadoFinal.style.display = "none";
  botonTerminar.style.display = "none";

  renderQuiz();
  actualizarContador();
});

botonSegundaPrueba.addEventListener("click", () => {
  for (let i = 0; i < respuestasUsuario.length; i++) {
    respuestasUsuario[i] = null;
  }

  ordenPreguntas = preguntas
    .map((pregunta, i) => pregunta.grupo === "segunda-prueba-25-26" ? i : -1)
    .filter(i => i !== -1);

  simulacroActivo = false;
  segundaPruebaActiva = true;

  botonSimulacro.style.display = "none";
  botonSegundaPrueba.style.display = "none";
  botonVolver.style.display = "inline-block";
  resultadoFinal.style.display = "none";
  botonTerminar.style.display = "none";

  renderQuiz();
  actualizarContador();
});


botonVolver.addEventListener("click", () => {
  ordenPreguntas = preguntas.map((_, i) => i);
  simulacroActivo = false;
  segundaPruebaActiva = false;

  botonVolver.style.display = "none";
  botonSimulacro.style.display = "inline-block";
  botonSegundaPrueba.style.display = "inline-block";
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
  segundaPruebaActiva = false;
  botonVolver.style.display = "none";
  botonSimulacro.style.display = "inline-block";
  botonSegundaPrueba.style.display = "inline-block";
  resultadoFinal.style.display = "none";
  botonTerminar.style.display = "none";
  renderQuiz();
  actualizarContador();
  window.scrollTo({ top: 0, behavior: "smooth" });
});

renderQuiz();
actualizarContador();