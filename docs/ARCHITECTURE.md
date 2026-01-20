# Architecture Minishell - Diagramme Détaillé

## 📊 Vue d'ensemble du flux d'exécution

```
┌─────────────────────────────────────────────────────────────────────┐
│                         MINISHELL PRINCIPAL                          │
│                         (main() + boucle)                            │
└──────────────────────────┬──────────────────────────────────────────┘
                           │
        ┌──────────────────┼──────────────────┐
        │                  │                  │
        ▼                  ▼                  ▼
   ┌─────────┐      ┌──────────┐      ┌──────────────┐
   │  INIT   │      │ PROMPT & │      │  EXECUTION   │
   │ MODULE  │      │READLINE  │      │  BUILTINS    │
   └────┬────┘      └────┬─────┘      └──────┬───────┘
        │                │                    │
        ▼                ▼                    ▼
   Env vars        User input            Command run
   (t_env)          Raw string
                        │
                        ▼
                  ┌─────────────────┐
                  │    LEXER        │
                  │  (tokenization) │
                  └────────┬────────┘
                           │
                           ▼
                  ┌─────────────────┐
                  │    PARSER       │
                  │  (AST building) │
                  └────────┬────────┘
                           │
                           ▼
                  ┌─────────────────┐
                  │  TOKENS LIST    │
                  │     (t_token)   │
                  └────────┬────────┘
                           │
                           ▼
                  ┌─────────────────┐
                  │  EXECUTOR       │
                  │  (fork/execve)  │
                  └─────────────────┘
```

---

## 🏗️ Structure des modules

### 1️⃣ **MODULE INITIALISATION** (`minishell.c`)
**Responsabilité**: Démarrage et initialisation du shell

```
init_minishell()
    ├─> init_env()              ← Initialiser les variables d'environnement
    └─> Préparer structures (t_minishell)
```

**Structures utilisées**:
- `t_minishell` → Conteneur principal (env + tokens)
- `t_env` → Liste chaînée des variables d'environnement

---

### 2️⃣ **MODULE VARIABLES D'ENVIRONNEMENT** (`envir_vars.c`)
**Responsabilité**: Gérer les variables d'environnement (PATH, HOME, PWD, etc.)

```
init_env(t_env **env, char **envp)
    ├─> Créer une liste chaînée de t_env
    ├─> Parser envp (format NAME=VALUE)
    └─> Stocker chaque paire clé/valeur

t_env structure:
    ├─> name  (char*)    : Nom de la variable
    ├─> value (char*)    : Valeur de la variable
    └─> next  (t_env*)    : Pointeur vers la variable suivante
```

---

### 3️⃣ **MODULE PROMPT & READLINE** (`prompt.c`, `history.c`)
**Responsabilité**: Afficher le prompt et lire l'entrée utilisateur

```
prompt()
    ├─> Afficher le prompt
    ├─> readline()       ← Lire la ligne de l'utilisateur
    ├─> Gérer l'historique
    └─> Retourner la chaîne saisie

history.c (MSH_HIST = "~/.msh_history")
    ├─> Charger l'historique au démarrage
    ├─> Ajouter chaque commande à l'historique
    └─> Sauvegarder l'historique à la fin
```

---

### 4️⃣ **MODULE LEXER** (`lexer.c`)
**Responsabilité**: Tokenizer la ligne de commande (découper en tokens)

```
Entrée: "echo hello | cat > file.txt"

Process:
    1. Identifier les tokens:
       ├─> Mot-clé/Commande: "echo"
       ├─> Argument: "hello"
       ├─> Opérateur: "|"
       ├─> Commande: "cat"
       ├─> Opérateur: ">"
       └─> Fichier: "file.txt"
    
    2. Créer des nœuds t_token pour chaque
    3. Retourner liste chaînée de tokens

Types d'opérateurs reconnus:
    ├─> "|"    (pipe)
    ├─> ">"    (redirection simple)
    ├─> ">>"   (append)
    ├─> "<"    (input redirection)
    ├─> "&&"   (AND logique)
    └─> "||"   (OR logique)
```

**Structure t_token**:
```
t_token:
    ├─> command[]      (char**)  : Commande + arguments (tableau)
    ├─> next_operator  (char*)   : Opérateur suivant (|, >, &&, etc.)
    └─> token_next     (t_token*): Pointeur vers le token suivant
```

---

### 5️⃣ **MODULE PARSER** (`parsing.c`)
**Responsabilité**: Analyser les tokens et construire la structure d'exécution

```
parse(char *input)
    │
    ├─> Vérifier syntaxe valide
    │   ├─> Pas de pipe orphelin
    │   ├─> Parenthèses équilibrées
    │   └─> Redirections valides
    │
    ├─> Effectuer expansion:
    │   ├─> Variables d'environnement ($VAR)
    │   ├─> Wildcard (*, ?, [a-z])
    │   └─> Tilde (~) expansion
    │
    ├─> Créer liste de tokens
    │   └─> Appeler lexer.c
    │
    └─> Retourner t_token* (liste chaînée)
```

---

### 6️⃣ **MODULE EXÉCUTION** (À implémenter)
**Responsabilité**: Exécuter les commandes

```
execute()
    │
    ├─> POUR CHAQUE TOKEN:
    │   │
    │   ├─> Est-ce un BUILTIN?
    │   │   ├─> echo
    │   │   ├─> cd
    │   │   ├─> pwd
    │   │   ├─> exit
    │   │   ├─> env
    │   │   ├─> export
    │   │   └─> unset
    │   │
    │   ├─> OUI → Exécuter localement (pas de fork)
    │   │
    │   └─> NON → Exécuter externe:
    │       ├─> fork()
    │       ├─> Chercher binaire dans PATH
    │       ├─> execve()
    │       └─> wait()/waitpid()
    │
    ├─> GÉRER REDIRECTIONS:
    │   ├─> dup2() pour >  (output)
    │   ├─> dup2() pour <  (input)
    │   ├─> dup2() pour >> (append)
    │   └─> close() fichiers
    │
    └─> GÉRER PIPES:
        ├─> pipe() créer tube
        ├─> fork() pour chaque commande
        ├─> dup2() connecter stdin/stdout
        └─> wait() tous les enfants
```

---

### 7️⃣ **MODULE BUILTINS** (`src/buildin/`)
**Responsabilité**: Implémentation des commandes internes

```
BUILTINS:
│
├─> echo.c
│   ├─> Afficher texte
│   └─> Gérer -n (pas de newline)
│
├─> exit.c
│   ├─> Quitter le shell
│   └─> Gérer code de sortie
│
├─> env.c (DÉJÀ PRÉSENT)
│   ├─> Afficher variables d'environnement
│   └─> Exécuter commande dans nouvel env
│
├─> cd.c (À faire)
│   ├─> Changer de répertoire
│   ├─> Mettre à jour PWD
│   └─> Gestion ~ et -
│
├─> pwd.c (À faire)
│   └─> Afficher répertoire courant
│
├─> export.c (À faire)
│   ├─> Ajouter/modifier variable d'environnement
│   └─> Afficher variables exportées
│
└─> unset.c (À faire)
    └─> Supprimer variable d'environnement
```

---

### 8️⃣ **MODULE UTILITAIRES**
**Responsabilité**: Fonctions helper

#### `linked_list_utils.c`
```
Utilité générale pour listes chaînées:
    ├─> ft_lstadd_back()
    ├─> ft_lstadd_front()
    ├─> ft_lstclear()
    ├─> ft_lstdelone()
    ├─> ft_lstiter()
    ├─> ft_lstlast()
    ├─> ft_lstmap()
    ├─> ft_lstnew()
    └─> ft_lstsize()
```

#### `clean.c`
```
Nettoyage mémoire:
    ├─> free_tokens()       ← Libérer liste t_token
    ├─> free_env()           ← Libérer variables d'env
    └─> free_minishell()    ← Libérer structure principale
```

---

## 📋 Structures de données principales

### `t_minishell`
```c
typedef struct s_minishell {
    t_env        *env;        // Pointeur vers liste variables d'env
    t_token     *token;     // Pointeur vers liste de tokens
} t_minishell;
```

### `t_env` (Variables d'environnement)
```c
typedef struct s_environment_vars {
    char    *name;              // "PATH", "HOME", etc.
    char    *value;             // "/usr/bin:/bin", "/home/user", etc.
    struct s_environment_vars *next;  // Pointeur vers variable suivante
} t_env;
```

### `t_token` (Tokens/Commandes)
```c
typedef struct s_token {
    char        **command;      // ["echo", "hello", NULL]
    char        *next_operator; // "|", ">", ">>", "<", "&&", "||"
    struct s_token *token_next; // Pointeur vers token suivant
} t_token;
```

### `t_store`
```c
typedef struct s_store {
    int fd_history;             // File descriptor pour historique
} t_store;
```

---

## 🔄 Flux complet d'une commande

```
Utilisateur tape: ls -la | grep ".c" > output.txt

   │
   ▼
┌─────────────────────────────────────────┐
│ 1. READLINE (prompt.c)                  │
│    Entrée: "ls -la | grep ".c" > output.txt"
└─────────────────────────────────────────┘
   │
   ▼
┌─────────────────────────────────────────┐
│ 2. LEXER (lexer.c)                      │
│    Tokenize:                            │
│    - "ls -la"                           │
│    - Opérateur: "|"                     │
│    - "grep .c"                          │
│    - Opérateur: ">"                     │
│    - "output.txt"                       │
└─────────────────────────────────────────┘
   │
   ▼
┌─────────────────────────────────────────┐
│ 3. PARSER (parsing.c)                   │
│    - Vérifier syntaxe                   │
│    - Expansions ($VAR, ~, *)            │
│    - Retourner t_token list             │
└─────────────────────────────────────────┘
   │
   ▼
┌─────────────────────────────────────────┐
│ 4. EXECUTOR (À implémenter)             │
│    Pour chaque token:                   │
│    - fork() pour "ls"                   │
│    - fork() pour "grep"                 │
│    - Connecter pipes                    │
│    - Ouvrir "output.txt" en écriture    │
│    - wait() pour tous les enfants       │
└─────────────────────────────────────────┘
   │
   ▼
┌─────────────────────────────────────────┐
│ 5. RESULTAT                             │
│    Fichier output.txt créé avec résultat
└─────────────────────────────────────────┘
```

---

## 📝 Checklist d'implémentation

### ✅ FAIT
- [x] Structures de base (t_minishell, t_env, t_token)
- [x] Variables d'environnement (init_env)
- [x] Builtin env
- [x] Historique (readline support)

### ⏳ À FAIRE (PRIORITÉ HAUTE)
- [ ] **Lexer complet** → Tokenization correcte
- [ ] **Parser** → Analyse et expansion
- [ ] **Executor** → Pipes + redirections
- [ ] **Builtins**: echo, cd, pwd, exit, export, unset
- [ ] **Signaux** → Ctrl+C, Ctrl+D
- [ ] **Erreurs** → Messages d'erreur appropriés

### ⏳ À FAIRE (PRIORITÉ MOYENNE)
- [ ] Wildcard expansion (*, ?, [a-z])
- [ ] Guillemets/Apostrophes ("", '')
- [ ] Échappement (\)
- [ ] Variables spéciales ($?, $!)

### ❌ BONUS (NON REQUIS)
- [ ] Historique multi-session
- [ ] Completion readline
- [ ] Alias
- [ ] Fonctions

---

## 🔗 Dépendances entre modules

```
minishell.c
    ├─> init_env() [envir_vars.c]
    ├─> prompt() [prompt.c]
    │   ├─> readline() [readline library]
    │   ├─> history() [history.c]
    │   └─> Appelle lexer/parser
    │
    ├─> lexer() [lexer.c]
    │   └─> Crée t_token
    │
    ├─> parser() [parsing.c]
    │   ├─> Utilise envir_vars (expansions)
    │   └─> Crée t_token
    │
    ├─> execute() [À faire]
    │   ├─> Utilise envir_vars (PATH)
    │   ├─> Appelle builtins
    │   └─> fork/execve
    │
    ├─> builtins/ [src/buildin/]
    │   ├─> env.c
    │   ├─> echo.c
    │   ├─> exit.c
    │   ├─> cd.c
    │   ├─> pwd.c
    │   ├─> export.c
    │   └─> unset.c
    │
    ├─> linked_list_utils() [linked_list_utils.c]
    │   └─> Gestion listes t_env et t_token
    │
    ├─> clean() [clean.c]
    │   └─> free_tokens(), free_env()
    │
    └─> libft/ [mylibft/]
        └─> ft_* functions
```

---

## 🎯 Points clés à retenir

| Aspect | Détails |
|--------|---------|
| **Main loop** | while(1) → prompt() → parse() → execute() |
| **Signaux** | Signal handlers pour Ctrl+C, Ctrl+D |
| **Variables env** | Liste chaînée t_env, expansion $VAR |
| **Pipes** | fork() + pipe() + dup2() pour connexions |
| **Redirections** | dup2() pour >, >>, <, connaissance file desc |
| **Builtins** | Aucun fork, modification d'état du shell |
| **Externe** | fork() + execve() + wait()/waitpid() |
| **Mémoire** | free() tout avant exit, gestion fuites |

---

## 📚 Ressources utiles

```
Fonctions système importantes:
    - fork()        : Créer processus enfant
    - execve()      : Remplacer processus par programme
    - waitpid()     : Attendre processus enfant
    - pipe()        : Créer un tube
    - dup2()        : Rediriger file descriptors
    - open/close()  : Fichiers
    - signal()      : Gestion signaux
    - readline()    : Lire avec édition
    - strtok()      : Découper chaînes
```
