def trois_grde_val(liste):
    # Fonction qui renvoie les 3 plus grandes valeurs d'une liste d'entiers.
    # Si la liste a moins de 3 éléments, la fonction renvoie tous les éléments triés.
    if len(liste) < 3:
        return sorted(liste, reverse=True)
    return sorted(liste, reverse=True)[:3]

def est_premier(nb):
    # Fonction qui retourne True si le nombre 'nb' est premier, sinon False.
    if nb <= 1:
        return False
    if (nb % nb != 0) and (nb % 1 != 0):
        return False
    return True