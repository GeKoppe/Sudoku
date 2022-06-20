# Menü
Im Menü gibt es verschiedene Optionen, die man auswählen kann. Die Navigation erfolgt über die Pfeil-Tasten, die Enter-Taste (bestätigen) und die Escape-Taste (Abbrechen / beenden).

## Neues Spiel
Wählt man "Neues Spiel", erscheint ein Menü mit einer Auswahl von Schwierigkeiten:
<figure><img src="Bilder/NeuesSpiel.png" alt="NeuesSpiel" style="border:2px solid black" title="NeuesSpiel" /></figure>
Nach Auswahl wird automatisch ein zufälliges Sudoku generiert (im Bild beispielsweise ein leichtes):
<figure><img src="Bilder/LeichtesSpiel.png" alt="LeichtesSpiel" style="border:2px solid black" title="LeichtesSpiel" /></figure>
Die Schwierigkeitsgrade bedeuten:

- *Leicht*: 20 Zahlen fehlen
- *Mittel*: 35 Zahlen fehlen
- *Schwierig*: 50 Zahlen fehlen

## Spiel fortsetzen
Zunächst erfolgt eine Abfrage, ob das letzte gespeicherte Spiel geladen werden soll:
<figure><img src="Bilder/Fortsetzen.png" alt="Fortsetzen" style="border:2px solid black" title="Fortsetzen" /></figure>
Wird diese mit ja bestätigt, wird das letzte Spiel geladen.
## Datei laden
Eine Liste von 50 gespeicherten Spielen wird angezeigt. Nach Auswahl wird das entsprechende Spiel geladen.

## Sudoku Editor
Ein leeres Sudoku wird angezeigt, in das der / die SpielerIn ein eigenes Spiel schreiben kann:
<figure><img src="./Bilder/Editor.png" alt="Editor" style="border:2px solid black" title="Editor" /></figure>
Wenn das Spiel eingetragen ist und der / die SpielerIn Escape drückt, muss er / sie noch einen Namen eingeben:
<figure><img src="Bilder/EditorName.png" alt="EditorName" style="border:2px solid black" title="EditorName" /></figure>
Das eingegebene Sudoku wird nach Eingabe durch Enter als Datei abgespeichert und man gelangt wieder in das Hauptmenü.

# Sudoku Regeln
Das Spielfeld ist korrekt mit Zahlen von 1-9 zu füllen. Folgende Regeln müssen hierfür beachtet werden:

- Jede Zahl (1-9) darf in jeder Zeile nur ein einziges Mal vorkommen.
- Jede Zahl (1-9) darf in jeder Spalte nur ein einziges Mal vorkommen.
- Jede Zahl (1-9) darf in jedem umrandeten 3x3-Block nur einmal vorkommen.
# Sudoku spielen
- Der Cursor wird mit den Pfeiltasten bewegt.
- Eine Zahl wird über die Eingabe einer der Zahlen von 1-9 getätigt.
- Durch drücken von Escape wird das Spiel beendet.
- Durch drücken von **H** wird ein Hinweis generiert. Es können maximal 3 Hinweise generiert werden.
- Vom System gefüllte Zellen können nicht editiert werden.
- Die eigenen Eingaben sind in blauer Schrift.
- Die Hinweise sind in roter Schrift.