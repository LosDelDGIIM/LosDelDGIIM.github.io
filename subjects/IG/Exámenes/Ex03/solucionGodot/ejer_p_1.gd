extends MeshInstance3D

func _ready():
	# Creamos las tablas de vértices, colores e indices
	var vertices = PackedVector3Array([
		Vector3(-1, -1, 1), Vector3(0, -1, 1), Vector3(1,-1,1),
		Vector3(-1, -1, 0), Vector3(0, -1, 0), Vector3(1,-1,0),
		Vector3(-1, 1, 0), Vector3(0, 1, 0), Vector3(1,1,0),
		Vector3(-1, 1, -1), Vector3(0, 1, -1), Vector3(1,1,-1)
	])
	var colores = PackedColorArray([
		Color(1,1,1), Color(1,1,1), Color(1,1,1),
		Color(0.1,0.1,0.1), Color(0.1,0.1,0.1), Color(0.1,0.1,0.1), 
		Color(1,1,1), Color(1,1,1), Color(1,1,1),
		Color(0.1,0.1,0.1), Color(0.1,0.1,0.1), Color(0.1,0.1,0.1)
	])
	var indices = PackedInt32Array([
		0, 4, 1, 0, 3, 4, 1, 4, 5, 1, 5, 2,
		3, 6, 7, 3, 7, 4, 4, 7, 8, 4, 8, 5,
		6, 9, 10, 6, 10, 7, 7, 10, 11, 7, 11, 8
	])
	
	# Creamos y añadimos las tablas al mesh
	var tablas : Array = []
	tablas.resize(Mesh.ARRAY_MAX)
	tablas[Mesh.ARRAY_VERTEX] = vertices
	tablas[Mesh.ARRAY_INDEX] = indices
	tablas[Mesh.ARRAY_COLOR] = colores
	
	mesh = ArrayMesh.new()
	mesh.add_surface_from_arrays(Mesh.PRIMITIVE_TRIANGLES, tablas)
	
	# Especificamos el material
	var mat = StandardMaterial3D.new()
	mat.vertex_color_use_as_albedo = true
	mat.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED
	material_override = mat
