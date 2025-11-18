extends MeshInstance3D

@export var n := 10

func _ready():
	# Definimos la SurfaceTool auxiliar
	var st := SurfaceTool.new()

	st.begin(Mesh.PRIMITIVE_TRIANGLES)

	# Relleno dos arrays de puntos con los 
	# puntos de la circunferencia interior y exterior (SUPERIOR)
	
	var r : float = 3
	var R : float = 4
	var c_1 := Vector3(-3.5,0,0)
	var c_2 := Vector3(3.5,0,0)

	var c_peque := PackedVector3Array([])
	var c_grande := PackedVector3Array([])

	# Meto sus respectivos puntos en cada circunferencia
	var ang_step := PI/(n-1)
	for i in range(n):
		# Desde -XX hasta -X
		var ang : float
		var p_peque : Vector3
		var p_grande : Vector3
		
		ang = PI/2-i*ang_step
		p_peque = c_1 + r*Vector3(-sin(ang),0,-cos(ang))
		p_grande = c_1 + R*Vector3(-sin(ang),0,-cos(ang))

		
		c_peque.push_back(p_peque)
		c_grande.push_back(p_grande)
	
	for i in range(1,n): # Desde 1 hasta n-1
		var p_peque_ant = c_peque[i-1]
		var p_peque = c_peque[i]
		var p_grande_ant = c_grande[i-1]
		var p_grande = c_grande[i]
		
		# Añadimos los dos triángulos
		st.add_vertex(p_peque_ant)
		st.add_vertex(p_grande_ant)
		st.add_vertex(p_peque)
		
		st.add_vertex(p_peque)
		st.add_vertex(p_grande_ant)
		st.add_vertex(p_grande)
		
	# LA DE ABAJO
		
	var c_peque_a := PackedVector3Array([])
	var c_grande_a := PackedVector3Array([])
	
	for i in range(n):
		# Desde X hasta XX
		var ang : float
		var p_peque : Vector3
		var p_grande : Vector3
		
		ang = PI/2+i*ang_step
		p_peque = c_2 + r*Vector3(-sin(ang),0,-cos(ang))
		p_grande = c_2 + R*Vector3(-sin(ang),0,-cos(ang))

		print("i:",i,"\nang:",ang,"\np_peque:",p_peque.x,",",p_peque.z)
		
		c_peque_a.push_back(p_peque)
		c_grande_a.push_back(p_grande)
		
			
	for i in range(1,n): # Desde 1 hasta n-1
		var p_peque_ant = c_peque_a[i-1]
		var p_peque = c_peque_a[i]
		var p_grande_ant = c_grande_a[i-1]
		var p_grande = c_grande_a[i]
		
		# Añadimos los dos triángulos
		st.add_vertex(p_peque_ant)
		st.add_vertex(p_peque)
		st.add_vertex(p_grande_ant)

		
		st.add_vertex(p_peque)
		st.add_vertex(p_grande)
		st.add_vertex(p_grande_ant)
	
	## Para quitar vértices repetidos (ns)
	st.index()

	# Damos valor al campo mesh de MeshInstance3D
	var malla := st.commit()
	mesh = malla


	# Damos valor al campo material_override de MeshInstance3D
	var mat := StandardMaterial3D.new()
	mat.vertex_color_use_as_albedo = true
	mat.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED
	material_override = mat
