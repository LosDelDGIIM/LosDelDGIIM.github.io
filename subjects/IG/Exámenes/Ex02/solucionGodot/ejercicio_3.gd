extends MeshInstance3D

func generaCubo(w : int, h : int) -> MeshInstance3D:
	var vertices = PackedVector3Array([
		Vector3(0,0,0), Vector3(0,0,w), Vector3(-w,0,w), Vector3(-w,0,0),
		Vector3(0,h,0), Vector3(0,h,w), Vector3(-w,h,w), Vector3(-w,h,0)
	])
	var indices = PackedInt32Array([2, 1, 0, 2, 0, 3, 4, 5, 6, 4, 6, 7,
		0, 4, 5, 0, 5, 1, 6, 5, 1, 6, 1, 2, 7, 6, 2, 7, 2, 3, 0, 4, 7, 0, 7, 3])
	var colores = PackedColorArray([])
	
	for v in vertices:
		colores.append(Color(1,1,1))
	
	var tablas : Array = []
	tablas.resize(Mesh.ARRAY_MAX)
	tablas[Mesh.ARRAY_VERTEX] = vertices
	tablas[Mesh.ARRAY_INDEX] = indices
	tablas[Mesh.ARRAY_COLOR] = colores

	var malla = ArrayMesh.new()
	malla.add_surface_from_arrays(Mesh.PRIMITIVE_TRIANGLES, tablas)
	
	var mat = StandardMaterial3D.new()
	mat.vertex_color_use_as_albedo = true
	mat.cull_mode = BaseMaterial3D.CULL_DISABLED
	mat.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED
	
	var inst = MeshInstance3D.new()
	inst.mesh = malla
	inst.material_override = mat
	return inst

func _ready():
	var w = 1
	var h = 1
	
	var padre = generaCubo(w,h)
	add_child(padre)
	
	var hijo = generaCubo(w,h)
	padre.add_child(hijo)
	hijo.position = Vector3(0,h,0)

var activo = false
var encoger = false
var contador = 0
var MAX = 50

var sentido_giro = true
var velocidad_giro = 100
var contador_giro = 2*MAX

func _process(delta):
	if Input.is_action_just_pressed("activar_cubos"):
		activo = !activo
		
	if activo:
		var p = get_child(0)
		var h = get_child(0).get_child(0)
		
		# Escalamos el padre
		if encoger:
			p.scale += Vector3(0,1,0) * delta
			contador += 1
			if contador >= MAX: encoger = !encoger
		else:
			p.scale -= Vector3(0,1,0) * delta
			contador -= 1
			if contador <= 0: encoger = !encoger
			
		# Giramos el hijo:
		if !sentido_giro:
			h.rotation += Vector3(0,0,deg_to_rad(velocidad_giro * delta))
			contador_giro += 1
			if contador_giro >= 2*MAX: sentido_giro = !sentido_giro
		else:
			h.rotation -= Vector3(0,0,deg_to_rad(velocidad_giro * delta))
			contador_giro -= 1
			if contador_giro <= 0: sentido_giro = !sentido_giro

# OJO: Con esta solución el cubo hijo también se escala, no sabemos cómo resolver el ejercicio de forma que
# se mantenga la herencia y que el hijo rote a la vez que mantiene su escala, modificando la escala del padre
