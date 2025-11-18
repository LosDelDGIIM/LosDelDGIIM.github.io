extends MeshInstance3D

func _ready():
	# Definimos los Arrays de la SOA
	var vertices := PackedVector3Array([])
	var triangulos := PackedInt32Array([])
	var colores := PackedColorArray([])


	# Rellenamos vértices
	var p0 := Vector3(-1,0,1)
	var p1 := Vector3(0,0,1)
	var p2 := Vector3(0,-1,1)
	var p3 := Vector3(1,-1,1)
	
	var p4 := Vector3(-1,0,0)
	var p5 := Vector3(0,0,0)
	var p6 := Vector3(0,-1,0)
	var p7 := Vector3(1,-1,0)
	
	var p8 := Vector3(-1,1,0)
	var p9 := Vector3(0,1,0)
	var p10 := Vector3(1,1,0)
	var p11 := Vector3(1,0,0)
	
	vertices.append_array(PackedVector3Array([
		p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11,
	]))


	# Rellenamos triángulos
	triangulos.append_array(PackedInt32Array([
		0,4,1,
		1,4,5,
		2,1,5,
		2,5,6,
		2,6,3,
		3,6,7,
		
		4,8,5,
		5,8,9,
		5,9,11,
		11,9,10,
		
		6,5,7,
		7,5,11,
		
	]))

	var b := Color(1,1,1)
	var g := Color(0.3,0.3,0.3)
	# Rellenamos colores
	colores.append_array(PackedColorArray([
		b, b, g, b,
		g,g,g,b,
		b,b,b,b
		
	]))


	# -------------------------------------------------------------
	# Completamos el SOA
	var tablas : Array = []
	tablas.resize(Mesh.ARRAY_MAX)
	tablas[Mesh.ARRAY_VERTEX] = vertices
	tablas[Mesh.ARRAY_INDEX]  = triangulos
	tablas[Mesh.ARRAY_COLOR] = colores


	# Damos valor al campo mesh de MeshInstance3D
	var malla := ArrayMesh.new()
	malla.add_surface_from_arrays(Mesh.PRIMITIVE_TRIANGLES, tablas)
	mesh = malla


	# Damos valor al campo material_override de MeshInstance3D
	var mat := StandardMaterial3D.new()
	mat.vertex_color_use_as_albedo = true
	mat.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED
	material_override = mat
