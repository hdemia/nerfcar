# Nerf Car

Progetto completo di auto controllabile via wifi con annesso "nerf launcher".

Questo progetto sfrutta la semplicità del codice Arduino combinata con le possibilità WiFi consentite dall'upgrade a Jolly.

Nato per essere realizzato in un fablab, questo progetto include progetti per componenti da stampare in 3d ed anche parti da stampare tramite incisore a laser. 

Il lancia-nerf prende ispirazione dal progetto [Nerf Turret di Nathan Li](https://www.thingiverse.com/thing:4870102): i modelli sono stati copiati da quel progetto ed adattati al telaio ed ai motori

## BOM
- Arduino Uno 
- Jolly upgrade (https://jolly-dev.com/)
- 4x Motore 5v mini
- 1x L298N
- 1x Micro Servo (qualunque modello dovrebbe andare bene, nel nostro caso Miuzei MF90)
- kit ruote + supporto motore (purtroppo non abbiamo le specifiche esatte, aggiungeremo presto il modello stampabile di supporti e ruote)
- PLA per la stampa della maggior parte dei pezzi
- Fogli di compensato da 3mm di spessore per il taglio dei telai

## Struttura del progetto

- `/`
- `/ino` Codice sorgente per Arduino
- `/web` Sistema di pilotaggio [disponibile qui](https://hdemia.github.io/nerfcar/)
- `/stl` Modelli da stampare/tagliare
    - `frame.svg` Telaio da tagliare a laser (2 volte)
    - `launcher_*` Componenti del lancia-nerf
