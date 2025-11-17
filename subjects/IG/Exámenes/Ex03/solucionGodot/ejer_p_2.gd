extends MeshInstance3D

var n = 3		# nº de cuadrados extra en dirección del eje x
var m = 2		# nº de cuadrados extra en dirección del eje z	

func ArrayMeshRejilla(ejex: int, ejez: int) -> ArrayMesh:
	# Creamos las tablas de vértices e indices
	# Creamos en primer lugar el cuadrado del centro
	var vertices = PackedVector3Array([
		Vector3(0,0,0), Vector3(1,0,0), Vector3(1,0,1), Vector3(0,0,1)
	])
	var indices = PackedInt32Array([0, 1, 2, 0, 2, 3])
	
	# Creamos 2*ejez triangulos extra en la direccion del eje z
	var comienzaz = 4	# indice del primer vertice a indexar de este tipo
	var cordz = 2 		# coordenada de comienzo de los vértices
	for i in range(ejez):
		# Creamos 2 vértices más
		vertices.append_array([
			Vector3(1, 0, cordz),
			Vector3(0, 0, cordz)
		])
		cordz += 1
		
		# Creamos los triángulos correspondientes a dichos vértices
		indices.append_array([
			comienzaz, comienzaz-1, comienzaz-2,
			comienzaz, comienzaz+1, comienzaz-1
		])
		comienzaz += 2
	
	# Creamos el primer cuadrado que va en la dirección del eje x
	var comienzax = 4 + 2*m		# indice del primer vertice a indexar de este tipo
	var cordx = 2				# coordenada de comienzo de los vértices
	if ejex >= 1:
		vertices.append_array([
			Vector3(cordx, 0, 0),
			Vector3(cordx, 0, 1)
		])
		cordx += 1
		
		indices.append_array([
			1, comienzax, comienzax+1,
			1, comienzax+1, 2
		])
		comienzax += 2
		
	# Creamos los 2*ejex-2 triangulos extra en la direccion del eje x
	for i in range(1,ejex):
		# Creamos 2 vértices más
		vertices.append_array([
			Vector3(cordx, 0, 0),
			Vector3(cordx, 0, 1)
		])
		cordx += 1
		
		# Creamos los triángulos correspondientes a dichos vértices
		indices.append_array([
			comienzax-2, comienzax, comienzax+1,
			comienzax-2, comienzax+1, comienzax-1
		])
		comienzax += 2
	
	# Creamos las tablas
	var tablas : Array = []
	tablas.resize(Mesh.ARRAY_MAX)
	tablas[Mesh.ARRAY_VERTEX] = vertices
	tablas[Mesh.ARRAY_INDEX] = indices
	
	var malla = ArrayMesh.new()
	malla.add_surface_from_arrays(Mesh.PRIMITIVE_TRIANGLES, tablas)
	return malla

func _ready():
	# Obtenemos el mesh de la rejilla
	mesh = ArrayMeshRejilla(n, m)
	
	# Le añadimos un material
	var mat = StandardMaterial3D.new()
	mat.albedo_color = Color(1,1,1,1)
	mat.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED
	material_override = mat
