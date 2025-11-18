extends Node3D


var ang := PI/6
var ancho = 0.3
var alto = 2


func ArrayMeshCubo24() -> ArrayMesh:
	var vertices := PackedVector3Array([])
	var triangulos := PackedInt32Array([])

	for h in 3:
		for i in 2:
			for j in 2:
				for k in 2:
					vertices.push_back(Vector3(i-0.5, j-0.5, k-0.5))

	triangulos.append_array(PackedInt32Array([
		## Frente (normal en −Z)
		1, 7, 5,
		1, 3, 7,

		## Atrás (normal en +Z)
		8, 4, 2,
		4, 6, 2,

		## Izquierda (normal en −X)
		1+8, 2+8, 3+8,
		1+8, 8,   2+8,

		## Derecha (normal en +X)
		5+8, 7+8, 6+8,
		5+8, 6+8, 4+8,

		## Arriba (normal en +Y)
		2+16, 6+16, 3+16,
		3+16, 6+16, 7+16,

		## Abajo (normal en −Y)
		1+16, 5+16, 4+16,
		1+16, 4+16, 16,
	]))
	var normales := Utilidades.calcNormales(vertices, triangulos)

	var tablas : Array = []
	tablas.resize(Mesh.ARRAY_MAX)
	tablas[Mesh.ARRAY_VERTEX] = vertices
	tablas[Mesh.ARRAY_INDEX]  = triangulos
	tablas[Mesh.ARRAY_NORMAL] = normales

	var mesh = ArrayMesh.new()
	mesh.add_surface_from_arrays(Mesh.PRIMITIVE_TRIANGLES, tablas)
	return mesh


func _ready() -> void:
	# Importante que tenga medida 1 para hacer bien las transformaciones
	var mcubo : ArrayMesh = ArrayMeshCubo24()
	# ------------------ BASE
	
	var mesh_base := MeshInstance3D.new()
	mesh_base.mesh = mcubo
	
	var mat_base = StandardMaterial3D.new()
	mat_base.albedo_color = Color(1,0,0)
	mesh_base.material_override = mat_base
	
	mesh_base.scale = Vector3(ancho,alto,ancho)
	mesh_base.position = Vector3(0,alto/2,0)
	
	add_child(mesh_base)
	
	var nodo_aux := Node3D.new()
	nodo_aux.position = Vector3(-ancho/2,alto,0)
	add_child(nodo_aux)

	
	var mesh_segundo := MeshInstance3D.new()
	mesh_segundo.mesh = mcubo
	
	var mat_segundo = StandardMaterial3D.new()
	mat_segundo.albedo_color = Color(0,1,0)
	mesh_segundo.material_override = mat_segundo
	
	mesh_segundo.translate(Vector3(ancho/2,alto/2,0))
	mesh_segundo.scale = Vector3(ancho,alto,ancho)

	var pivote := Node3D.new()
	pivote.rotate_z(ang)
	nodo_aux.add_child(pivote)
	
	pivote.add_child(mesh_segundo)
	
	# ------ top
	var nodo_aux_top := Node3D.new()
	pivote.add_child(nodo_aux_top)
	nodo_aux_top.translate(Vector3(0,alto,0))
	

	var pivote_top := Node3D.new()
	pivote_top.rotate_z(ang)
	nodo_aux_top.add_child(pivote_top)
	
	
	var mesh_top := MeshInstance3D.new()
	mesh_top.mesh = mcubo
	
	var mat_top = StandardMaterial3D.new()
	mat_top.albedo_color = Color(0,0,1)
	mesh_top.material_override = mat_top
	
	mesh_top.translate(Vector3(ancho/2,alto/2,0))
	mesh_top.scale = Vector3(ancho,alto,ancho)
	
	pivote_top.add_child(mesh_top)

	

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
