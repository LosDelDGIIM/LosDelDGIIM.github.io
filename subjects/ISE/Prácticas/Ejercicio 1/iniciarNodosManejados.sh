#!/bin/bash

# Variables
CONFIG_HOST="./hosts_config.yaml"
CONFIG_PLAYBOOK="./playbook_config.yaml"

# 1. Ejecución playbook de configuración
ansible-playbook -i $CONFIG_HOST $CONFIG_PLAYBOOK