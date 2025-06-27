#!/bin/bash

# Variables
HOST="./hosts_server.yaml"
PLAYBOOK="./playbook_server.yaml"

# 1. Ejecución playbook de configuración
ansible-playbook -i $HOST $PLAYBOOK