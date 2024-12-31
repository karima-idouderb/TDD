import math 

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
    for i in range(2, int(math.sqrt(nb)) + 1):
        if nb % i == 0:
            return False
    return True

def est_suite_arith(liste, epsilon=1e-9):
    # Fonction qui renvoie si la liste représente ou pas une suite arithmétique.
    if len(liste) < 2:
        return True
    diff = liste[1] - liste[0]
    for i in range(1, len(liste) - 1):
        if abs(liste[i + 1] - liste[i] - diff) > epsilon:
            return False
    return True

def fifo(action, val=None, etat={"queue": []}):
    if action == "enqueue":
        if val is None:
            raise ValueError("A value must be provided for 'enqueue'")
        etat["queue"].append(val)
        return None

    elif action == "dequeue":
        if len(etat["queue"]) == 0:
            return etat["queue"].pop(0)
    
    elif action == "taille":
        return len(etat["queue"])
    