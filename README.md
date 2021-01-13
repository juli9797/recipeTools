# Rezept Tools

Ein kleines Tool für ein Markdown basiertes Rezeptformat.
Rezepte können zur Datenbankspeicherung (z.B. MongoDB) in JSON gewandelt werden.

ToDO:

* Format validierung
* JSON -> Markdown

## Installation

Es wird nur g++ mit c++ 20 support benötigt.
'make install'

## Benutzung

Zur Umwandlung von markdown zu JSON:
'recipeTools [files]'

## Rezeptformat

Es wird zwingend ein Rezepttitel '# Titel' am Anfang des Dokuments erwartet.
Alle weiteren Felder sind unter Level 2 Überschriften wie Beispielsweise `## Zubereitung`
eingeordnet. Tags werden im Abschnitt `## Tags` mit einem Backtick umschlossen aufgeführt.
Bullet Lists enthalten immer einen Schlüssel dem ein Wert mit einem `:`
zugewiesen werden kann. Unter `## Information` ist ein Punkt `Kosten` vorgesehen
, dieser kann Werte von 1-4 annehmen.
Alles weitere sollte im Template.md ersichtlich sein.

