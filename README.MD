<h1 align="center">Idée d'architecure</h1>

# <ins>Micro module-pipeline architecture:</ins>
&emsp;Le but est de faire en sorte de pouvoir charge different module pour chaque partie de traitement de donné, sur differentes pipelines. Les thematique lier a ce type d'architecture:

- Traitement des donné

&emsp;La première et plus importante des choses a comprendre est qu'une pipeline est un module avec un un fonctionnement specifique à ca tache: transmettre et recevoir des donnees.

## <ins>Qu'est ce qu'un module:</ins>

Un module est une partie du code qui serat externallement charge par la pipeline (defini endessous), puis utilise pour traite la donné a l'aide de different processus.

## <ins>Qu'est ce qu'une pipeline:</ins>

&emsp;Une pipeline est une chaine de module, avec **1 API d'entre** et **1 API de retour**. Elle va faire passer les donnes entré dans tout les modules pour verifier si ils sont capable de gere la donnée, puis retourne different résultat en fonction de la vérification.
&emsp;Les modules que la pipeline utilise peuvent être enregistee de differente magniere, donc cette partie du code peut varie en fonction de vos besoins:
&emsp;Un module est enregistré dans la pipeline grace à une librairi externe (.dll) chargé grace à une configuration ou une CLI, qui va appelé les fonctions disponnibles dans le module pour traité la donnée.
&emsp;Une pipeline aura pour la plus part du temps une **queue thread safe** pour eviter de bloqué le fonctionnement du core ou d'une autre pipeline, avant la réception du retour du module.

## <ins>Communication entre module:</ins>

&emsp;les modules communique entre eux (car une pipeline est un module) pour traité la donnée recu par une API d'entre et renvoié le résultat à API de retour.

- Le **module principale** dans la configuration va chargé tout les autres modules qui lui sont assignés, puis les configure.
- Le **module secondaire** va etre utilise comme un module unique (defini plus bas) par default, donc dans la configuration de votre module, il faudra modifier ca valeur. Il va permettre de faire des traitememt sur les donne rentre et changer letat du module.

## <ins>Module non unique:</ins>

&emsp;Une unique API suffit pour utilise un module, mais en avoir deux permet de mieux séparé la gestion d'entré des données et la gestion de sortie.
&emsp;Les 2 API doivent etre **commune a tout les modules** et doivent avoir les differentes fonctionnalité implementés dans la pipeline qui charge les module:

- **Configuration**: avoir un ou plusieur type de fonction permettant de configure le module et une fonction **config** qui va etre utilise par la pipeline pour configuré le module au lancement.
- **Traitement**: plusieur fonction qui vont prendre en entre de la donnée et renvoie de une nouvelle donnée.

&emsp;Le module va appelé la fonction **config** qui va donne tout les fonctions disponnible prise en charge par ce module et auront une signature défini dans l'API d'entré.
&emsp;La gestion des fonctions retourné par l'appel de la fonction **config** sont enregistre par la pipeline et assigé au module. Apres avoir vérifié que la donnée est gérè par le module, elle est envoié a la fonction assigne.

## <ins>Module unique:</ins>

&emsp;Un module unique est un type de module gérè par la pipeline, qui utilise une API par défault qui permet uniquement la configuration et le traitement des données, avec la fonction **config** pour la configuration et **process** pour le traitement des données.
&emsp;Ce type de module éxiste pour le dévellopement de module basique, qui ne sont pas voue à évoluze ou être maintenu.

Mais il peut etre utilise comme retour par défault d'une pipeline.
- Le retour de la fonction config va uniquement configure le module.
- La fonction process va traite la donne statiquement.

## <ins>Module evenement:</ins>

&emsp;Dans une pipeline l'entré peut être directement faite dedans. Les modules événement vont **stocké une queue** qui va être remplis par les données reçu, et va ensuite directememt envoié au module les données reçu, sans passé par une autre pipeline.
&emsp;Ce module est base sur le module non unique. Le fonctionnement des fonctions retourne par process, auront une signature retournant une structure de status de module et prendra des arguement definie dans l'API l'utilisant.

## <ins>Simple pipeline:</ins>

&emsp;C'est une pipeline ou l'on peut charge uniquement des modules, cela permet de bloque virtuellement le grosissement de la pipeline en n'en chargeant.
&emsp;Ce type se pipeline utilise les fonctionnements par defaut d'un module unique.

## <ins>Pipeline grouping:</ins>

&emsp;Le pipeline grouping est type de pipeline qui peuvent charge un module, mais aussi une pipeline, ce qui permet d'avoir des groupes de pipelines reutilisable dans un projet (par exemple en fonction un protocle de communication).
&emsp;Il y aura 4 API differentes:

- **API d'entre**: pour que la pipeline qui la charge puisse configure le module a la demande et recevoir des requetes.
- **API de retour**: pour le renvoie de donne apres traitement.
- **API module**: utilise pour charge, decharge et communique avec un module.
- **API pipeline**: permet de charge, decharge et communique avec une autre pipeline.

&emsp;Le fonctionnement des API d'entre et de sortie sont implement par la pipeline, donc pas besoin d'y reflechire.
&emsp;La pipeline principale doit s'occupe en premier lieux de charger les modules et la pipeline en asynchrone, puis de charger et configure les modules de la pipeline secondaire.
&emsp;Le fonctionnement de communication entre une pipeline et un module ne change pas.

## <ins>Exemple:</ins>

### Implementation d'une pipeline reseau avec un module évenement:

La pipeline réseau est une pipeline simple, utilisant un module d'évenement en entré. Elle posséde une configuration interne: "mettre en place la connection des sockets et lance la pipeline", mais aussi 2 modules:

- **Reception**: traitement des données reçu par les differents sockets.
- **Erreur**: gestion d'erreur de la requête.

&emsp;Pour commence il faut cree une API pour que les modules puissent communiqué enssemble et que la pipeline communique avec le core.

&emsp;La pipeline connect la queue que la connxion interne à prise en paramètre et va envoié toutes les nouvelles donées reçu via le réseau, vers le module de **Reception**, si celui ci n'accepte pas les données alors ensuite les données seront envoié au module d'**Erreur**

#### Connexion interne:

&emsp;Quand la fonction **config** est appelé, elle lance un thread qui va accepté toutes connections sur le port fourni en paramétre, puis ajouter les sockets qui vient de ce connecté à la **liste des connections**. Ensuite met en place la recéption de **nouvelle donnée via les sockets**, qui va être traité par le module **Reception** ou **Erreur** de la pipeline.

_______

<br />
<br />
<h1 align="center">~ : ~</h1>
<br />
<br />

_______

<h1 align="center">Programme de prévision de bénéfice</h1>

## <ins>Buisness model cible:</ins>

#### Le buisness model ciblé est une application avec abonnement mensuel et/ou annuel

## C'est quoi l'idée:

on prend les données de l'anné précedente de l'application cible, puis crée des prévision sur l'année futur et pouvoir s'auto corrigé tout les mois.

## Fonctionnement:

### Donnée:

- **Nombre d'abonnement** (par jour)
- **Nombre de connection** (par jour)
- **Nombre de visite** (par jour)
- **temps d'utilisation** (par jour)

### Prévision:

Les prévisions prendront toutes les données et cherchera à genere une fonction qui donnera les hestimations des différentes données.

### Auto correction:

_______

<br />
<br />
<h1 align="center">~ : ~</h1>
<br />
<br />

_______

