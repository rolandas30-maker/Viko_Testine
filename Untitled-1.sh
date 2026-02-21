#!/bin/bash
# ...existing code...
# Patikrinti failą: išveda pranešimus ir grąžina 0 jei egzistuoja, 1 jei ne
check_file() {
    local f="$1"
    if [ -f "$f" ]; then
        if [ -x "$f" ]; then
            echo "Failas '$f' yra vykdomasis."
        else
            echo "Failas '$f' NĖRA vykdomasis."
        fi
        return 0
    else
        echo "Failas '$f' neegzistuoja arba nėra paprastas failas."
        return 1
    fi
}

# Įvedimas / argumentai
if [ -z "$1" ]; then
    echo "Įveskite pirmą failą:"
    read -r file1
else
    file1=$1
fi

if [ -z "$2" ]; then
    echo "Įveskite antrą failą:"
    read -r file2
else
    file2=$2
fi

# Patikriname, ar keliai skirtingi
if [ "$file1" = "$file2" ]; then
    echo "Įspėjimas: abu įvesti failai yra identiški ('$file1')."
fi

# Patikrinimai
check_file "$file1"
res1=$?
check_file "$file2"
res2=$?

if [ $res1 -eq 0 ] && [ $res2 -eq 0 ]; then
    echo "Abu failai egzistuoja ir buvo patikrinti."
    exit 0
else
    echo "Vienas arba abu failai neegzistuoja arba nėra paprasti failai."
    exit 1
fi
# ...existing code...