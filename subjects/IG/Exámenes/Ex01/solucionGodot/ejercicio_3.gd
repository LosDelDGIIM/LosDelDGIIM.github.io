extends MeshInstance3D

func generaCubo(lado : float, alto : float, traslado : Vector3 = Vector3(0,0,0)) -> MeshInstance3D:
	var vertices = PackedVector3Array([Vector3(-lado/2,0,-lado/2), Vector3(lado/2,0,-lado/2), Vector3(lado/2,0,lado/2), Vector3(-lado/2,0,lado/2),
					Vector3(-lado/2,alto,-lado/2), Vector3(lado/2,alto,-lado/2), Vector3(lado/2,alto,lado/2), Vector3(-lado/2,alto,lado/2)])
	for i in range(vertices.size()):
		vertices[i] += traslado
	var indices = PackedInt32Array([0, 3, 2, 0, 2, 1, 4, 5, 6, 4, 6, 7,
		7, 6, 2, 7, 2, 3, 6, 5, 1, 6, 1, 2, 5, 4, 0, 5, 0, 1, 4, 7, 3, 4, 3, 0])
	var colores = PackedColorArray([])
	
	for v in vertices:
		colores.append(Color(1,1,1))

	var tablas : Array = []
	tablas.resize(Mesh.ARRAY_MAX)
	tablas[Mesh.ARRAY_COLOR] = colores
	tablas[Mesh.ARRAY_INDEX] = indices
	tablas[Mesh.ARRAY_VERTEX] = vertices
	var malla = ArrayMesh.new()
	malla.add_surface_from_arrays(Mesh.PRIMITIVE_TRIANGLES, tablas)

	var mat = StandardMaterial3D.new()
	mat.vertex_color_use_as_albedo = true
	mat.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED
	mat.cull_mode = BaseMaterial3D.CULL_DISABLED
	
	var meshinst = MeshInstance3D.new()
	meshinst.mesh = malla
	meshinst.material_override = mat
	return meshinst

func _ready():
	var w = 1.5
	var h = 0.2
	var altura = 0.1
	var altura2 = 0.2
	assert(w>1, "w debe ser mayor que 1")
	assert(h<0.3, "h debe ser menor que 0.3")
	# *************
	
	var CuboPrincipal = generaCubo(w, altura)
	CuboPrincipal.position = Vector3(w/2,0,w/2)
	add_child(CuboPrincipal)
	
	var CuboHijo = generaCubo(h, altura2, Vector3((w-h)/2, 0, 0))
	get_child(0).add_child(CuboHijo)
	
var activo = false
var velocidad_giro = 10
var contador = 0
var MAX = 100
var encoger = false
func _process(delta):
	if Input.is_action_just_pressed("activar"):
		activo = !activo
	if activo:
		get_child(0).get_child(0).rotate(Vector3.UP, delta * velocidad_giro)
		
		if encoger:
			get_child(0).scale -= Vector3(0,1,0) * delta
			contador -= 1
			if contador <= 0: encoger = !encoger
		else:
			get_child(0).scale += Vector3(0,1,0) * delta
			contador += 1
			if contador >= MAX: encoger = !encoger
			
