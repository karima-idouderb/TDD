def trois_grde_val(liste):
    # Fonction qui renvoie les 3 plus grandes valeurs d'une liste d'entiers.
    # Si la liste a moins de 3 éléments, la fonction renvoie tous les éléments triés.
    return sorted(liste, reverse=True)[:3]