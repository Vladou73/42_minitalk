_Beaucoup de fonctions sont interdites dans un signal handler dont malloc et printf car ce sont des appels systemes.Si vous passez outre ce conseil, pour perdrez des signaux.
_Les operations *, % et / sont beaucoup plus lentes que les bitwise operations

Tu ne peux rien attacher à un signal.C ' est ton server dans lequel tu auras écrit une fonction " signal handler" qui va faire quelque chose lorsqu il recevra un signal.
Et comme tu n en as que 2 à ta disposition, tu n ' as qu un seul moyen de transmettre un char. Et comme un char fait 8 bits , celà nous fait un total de 8 signaux par caracteres

envoi ton PID avant ton message et stock le

le barème c'est 100 char en moins d'1s et 1000char en moins de 2s

le but du minitalk est d'avec l'utilisation de deux signal unix, d'implémenter un simple chat. Le but premier d'un signal n'est absolument pas de communiqué des données, il s'agit donc d'un exercice de réflexion et de débrouillardise. Quand tu lance un programme comme make sur un système UNIX, tu peux l'interrompre de manière prématuré en appuyant sur CRTL-C : dans ce cas le shell dans lequel tu as lancé ton programme envoie un signal à ton programme (SIGINT dans ce cas), pour qu'il se ferme immédiatement (liste des signaux disponibles https://www.linuxtricks.fr/wiki/signaux-unix-unix-signals)
Dans un programme, tu peux redéfinir le comportement des signaux. Si par exemple tu décide que lors de la réception d'un signal SIGINT, il ne ce passe rien tu peux, si tu veux afficher un message tu peux aussi. Ce genre de modification se passe grâce à un handler (une fonction qui gère) qui est exécuté lors de la réception d'un signal que tu aura décider. Pour cela, tu peux t'intéresser à la fonction signal pour commencer https://koor.fr/C/csignal/signal.wp
KooR.fr - signal - Langage C
Une description de la librairie C agrémentée de nombreux exemples
Image
Chaque processus système se voit attribuer un P.I.D (Processus IDentification) par le kernel pour chaque programme afin justement que chaque signal arrive bien à bon port et savoir à qui envoyer ce signal. Tu peux utiliser le commande top sur le shell pour visualiser les processus sur l’ensemble du système, et dans ton programme la fonction getpid(), qui te retourne un entier non signé.
Tu vera que la fonction signal est un peu limité et que tu va devoir utiliser sigaction pour pouvoir implémenter tout ça de manière fiable.
Sinon sur la forme tu as tout à fait raison : tu envoie à ton serveur chaque octet de ta chaîne de caractère. Une fois que tout ces octets sont reçu, on affiche le message.
Et ce qui est bien précisé sur le sujet, c'est que linux ne met pas en file d'attente les signaux. Par exemple : tu envoie 20 signaux en l'espace de 20 micro secondes, ton serveur reçois le signal : il va donc faire ce qu'il a à faire. Mais problème : en fonction du temps que ton serveur aura mis à faire ses petites affaires, il aura probablement loupé les 19 signaux derrières car l'éxécution de son action aura peut-être pris 30 micro secondes de temps système.
Par contre sur mac, tu as ce système de file d'attente. Je te conseille de le rendre compatible avec Linux car c'est bien plus intéressant (tu dois réaliser un système de file d'attente donc)
Pour la doc, man sigaction, man 2 kill, man signal..
# 42_minitalk



#include <signal.h>
// L'appel système sigaction() sert à modifier l'action effectuée par un processus à la réception d'un signal spécifique.
// signum indique le signal concerné, à l'exception de SIGKILL et SIGSTOP.
// Si act est non nul, la nouvelle action pour le signal signum est définie par act. Si oldact est non nul,
//  l'ancienne action est sauvegardée dans oldact


int sigaction(int signum, const struct sigaction *act,
	struct sigaction *oldact);


#include <signal.h>
The kill() system call can be used to send any signal to any process group or process.
int kill(pid_t pid, int sig);
If pid is positive, then signal sig is sent to the process with the ID specified by pid.

#include <sys/types.h>
#include <unistd.h>
// getpid() renvoie l'identifiant du processus appelant.
pid_t getpid(void);

