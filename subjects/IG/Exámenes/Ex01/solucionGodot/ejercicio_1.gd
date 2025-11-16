extends MeshInstance3D

func _ready():
	var vertices := PackedVector3Array([Vector3(0,0,0.5), Vector3(0,0,1), Vector3(1,0,0.5), Vector3(1,0,1),
										Vector3(1.1,0.5,0.5), Vector3(1.5, 0.5, 0.5), Vector3(1.5,0,1)])
	var indices := PackedInt32Array([0, 2, 1, 2, 3, 1, 2, 4, 3, 4, 5, 6, 4, 6, 3])
	var colores := PackedColorArray([Color(0,0,0), Color(0,0,0), Color(0,0,0), Color(0,0,0),
										Color(1,1,1), Color(1,1,1), Color(1,1,1)])
	
	var tablas : Array = []
	tablas.resize(Mesh.ARRAY_MAX)
	tablas[Mesh.ARRAY_VERTEX] = vertices
	tablas[Mesh.ARRAY_INDEX] = indices
	tablas[Mesh.ARRAY_COLOR] = colores
	
	mesh = ArrayMesh.new()
	mesh.add_surface_from_arrays(Mesh.PRIMITIVE_TRIANGLES, tablas)
	
	var mat = StandardMaterial3D.new()
	mat.vertex_color_use_as_albedo = true
	mat.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED
	mat.cull_mode = BaseMaterial3D.CULL_DISABLED
	material_override = mat
