#!/bin/bash
#Órdenes para el Gestor de carga de trabajo (no intercalar instrucciones del script)
#1. Asignar al trabajo un nombre
#SBATCH --job-name=SumaVectores
#2. Asignar el trabajo a una partición (cola) 
#SBATCH --partition=ac
#3. Asignar el trabajo a un account 
#SBATCH --account=ac
#4. Para que el trabajo no comparta recursos 
#SBATCH --exclusive
#5. Para que se genere un único proceso del sistema operativo que pueda usar un máximo de 12 núcleos
#SBATCH --ntasks 1 --hint=nomultithread
#Se pueden añadir más órdenes para el gestor de colas

#Obtener información de las variables del entorno del Gestor de carga de trabajo:
echo "Id. usuario del trabajo: $SLURM_JOB_USER"
echo "Id. del trabajo: $SLURM_JOBID"
echo "Nombre del trabajo especificado por usuario: $SLURM_JOB_NAME"
echo "Directorio de trabajo (en el que se ejecuta el script): $SLURM_SUBMIT_DIR"
echo "Cola: $SLURM_JOB_PARTITION"
echo "Nodo que ejecuta este trabajo:$SLURM_SUBMIT_HOST"
echo "Nº de nodos asignados al trabajo: $SLURM_JOB_NUM_NODES"
echo "Nodos asignados al trabajo: $SLURM_JOB_NODELIST"
echo "CPUs por nodo: $SLURM_JOB_CPUS_PER_NODE"


export OMP_DYNAMIC=False

# Necesario en PC personal, ya que no usamos Slurm
export OMP_PROC_BIND=spread    # Asignación de hebras a cores físicos

# El primer parámetro es el programa que queremos ejecutar
# El segundo parámetro es el tamaño del problema
programa=$1
size=$2

# El tercer parámetro es el número máximo de procesadores a usar
maxProc=$3

for (( i=1; i<=$maxProc; i++ ))
do
   # En Atcgrid: contamos con Slurm
   # srun -c $i $programa $size
   
   # En PC personal (no tenemos Slurm):
   export OMP_NUM_THREADS=$i       # Número de cores físicos
   $programa $size
done