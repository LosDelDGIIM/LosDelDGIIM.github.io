extends Node3D

func ArrayMeshCubo24() -> ArrayMesh:
	var vertices := PackedVector3Array([Vector3(-0.5,-0.5,-0.5), Vector3(-0.5,-0.5,-0.5), Vector3(-0.5,-0.5,-0.5), 
										Vector3(-0.5,-0.5,0.5), Vector3(-0.5,-0.5,0.5), Vector3(-0.5,-0.5,0.5), 
										Vector3(-0.5,0.5,-0.5), Vector3(-0.5,0.5,-0.5), Vector3(-0.5,0.5,-0.5), 
										Vector3(-0.5,0.5,0.5), Vector3(-0.5,0.5,0.5), Vector3(-0.5,0.5,0.5),
										Vector3(0.5,-0.5,-0.5), Vector3(0.5,-0.5,-0.5), Vector3(0.5,-0.5,-0.5),  
										Vector3(0.5,-0.5,0.5), Vector3(0.5,-0.5,0.5), Vector3(0.5,-0.5,0.5),  
										Vector3(0.5,0.5,-0.5), Vector3(0.5,0.5,-0.5), Vector3(0.5,0.5,-0.5),  
										Vector3(0.5,0.5,0.5), Vector3(0.5,0.5,0.5), Vector3(0.5,0.5,0.5)])
	var indices := PackedInt32Array([0, 4, 17, 0, 17, 13, 1, 12, 20, 1, 20, 7, 11, 3, 2, 11, 2, 6,
									 5, 9, 22, 5, 22, 15, 16, 23, 19, 16, 19, 14, 21, 10, 8, 21, 8, 18])
	var normales := PackedVector3Array([])
	
	normales = Utilidades.calcNormales(vertices, indices)
	
	var tablas : Array = []
	tablas.resize(Mesh.ARRAY_MAX)
	tablas[Mesh.ARRAY_VERTEX] = vertices
	tablas[Mesh.ARRAY_INDEX] = indices
	tablas[Mesh.ARRAY_NORMAL] = normales
	
	var malla = ArrayMesh.new()
	malla.add_surface_from_arrays(Mesh.PRIMITIVE_TRIANGLES, tablas)
	return malla

var ancho_patas = 0.1
var alto_patas = 1
var ancho_tablero = 1
var largo_tablero = 2
var alto_tablero = 0.1

func _ready():
	# El ArrayMesh de un cubo
	var mcubo = ArrayMeshCubo24()
	
	# Creamos los materiales
	var mat_tablero = StandardMaterial3D.new()
	mat_tablero.albedo_color = Color(0,0,1,1)
	mat_tablero.metallic = 0.3
	mat_tablero.roughness = 0.2
	mat_tablero.shading_mode = BaseMaterial3D.SHADING_MODE_PER_PIXEL
	
	var mat_patas = StandardMaterial3D.new()
	mat_patas.albedo_color = Color(1,0,0,1)
	mat_patas.metallic = 0.3
	mat_patas.roughness = 0.2
	mat_patas.shading_mode = BaseMaterial3D.SHADING_MODE_PER_PIXEL

	# Creamos los hijos
	var tablero = MeshInstance3D.new()
	tablero.mesh = mcubo
	tablero.material_override = mat_tablero
	add_child(tablero)

	for i in range(4):
		var pata = MeshInstance3D.new()
		pata.mesh = mcubo
		pata.material_override = mat_patas
		add_child(pata)

	# Escalamos y trasladamos los cubos para formar la mesa
	tablero.scale = Vector3(ancho_tablero, alto_tablero, largo_tablero)
	tablero.position = Vector3(0,alto_tablero/2.0 + alto_patas,0)

	# Para las patas, realizamos distintas traslaciones
	var traslaciones = [
		Vector3((ancho_tablero - ancho_patas)/2.0, 0, (largo_tablero - ancho_patas)/2.0),
		Vector3(-(ancho_tablero - ancho_patas)/2.0, 0, (largo_tablero - ancho_patas)/2.0),
		Vector3((ancho_tablero - ancho_patas)/2.0, 0, -(largo_tablero - ancho_patas)/2.0),
		Vector3(-(ancho_tablero - ancho_patas)/2.0, 0, -(largo_tablero - ancho_patas)/2.0)
	]
	for i in range(1,5):
		get_child(i).scale = Vector3(ancho_patas, alto_patas, ancho_patas)
		# Primero las colocamos horizontalmente y luego las trasladamos verticalmente
		get_child(i).position = traslaciones[i-1]
		get_child(i).position += Vector3(0,alto_patas/2.0,0)
