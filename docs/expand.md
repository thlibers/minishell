Comprendre les types d'expansion
Tu devras gérer plusieurs types d'expansion dans l'ordre suivant :

L'expansion de variables ($VAR, $?, $$)
L'expansion de tildes (~ vers $HOME)

Stratégie générale
Séparer le parsing de l'expansion : ton lexer/parser identifie les tokens, puis une phase d'expansion les transforme avant l'exécution.
Gérer les quotes :

Entre guillemets simples '...' : aucune expansion
Entre guillemets doubles "..." : expansion des variables uniquement, pas de wildcard
Sans quotes : toutes les expansions

Étapes pour l'expansion de variables

Parcourir chaque token après le parsing
Identifier les $ dans les tokens non-quotés simplement ou doublement quotés
Extraire le nom de variable (caractères alphanumériques et _ après le $)
Récupérer la valeur via getenv() ou tes variables d'environnement
Remplacer dans le token

Cas spéciaux :

$? : code de retour de la dernière commande
$$ : PID du shell (souvent ignoré dans minishell)
$ suivi d'un espace ou caractère invalide : ne pas expand

Ordre de traitement
Pour chaque token :

Vérifier le type de quotes
Faire l'expansion de variables si autorisée
Faire l'expansion de wildcard si autorisée (après les variables)
Retirer les quotes de délimitation

Pièges à éviter

Ne pas expand dans les quotes simples
Gérer $ en fin de chaîne ou suivi de caractères invalides
Le wildcard doit se faire après l'expansion de variables
Attention au word splitting (découpage sur espaces) après expansion