#!/bin/bash

# Usage : ./generate.sh <num_theme> <nb_exercices>

if [ $# -ne 2 ]; then
    echo "Usage : $0 <num_theme> <nb_sous_dossiers>"
    exit 1
fi

theme=$1
nb=$2

mkdir "theme_${theme}"

for ((i=1; i<=nb; i++)); do
    mkdir "theme_${theme}/exercice_${theme}_${i}"
done

echo "Création terminée."
