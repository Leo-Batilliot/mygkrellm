# 🖥️ MyGKrellm

> **GNU Krell Monitors – Clone C++**
>
> Projet **RUSH 4 – Epitech**  
> Un moniteur système modulaire, en **nCurses** et **SFML**, inspiré de **GKrellM**.

---

## 📌 Description

**MyGKrellm** est un moniteur système développé en **C++**, capable de s’exécuter aussi bien :
- en **mode texte** (terminal, via **nCurses**)
- qu’en **mode graphique** (fenêtre, via **SFML**)

Le projet repose sur une **architecture modulaire**, permettant d’afficher dynamiquement différentes informations système sous forme de **modules empilés verticalement**, à la manière de GKrellM.

---

## ✨ Fonctionnalités

### 🧩 Modules implémentés
- 👤 **Utilisateur & Hostname**
- 🖥️ **Système d’exploitation & Kernel**
- 🕒 **Date & Heure**
- ⚙️ **CPU** (activité, fréquence, cœurs, température)
- 🧠 **RAM**
- 🌐 **Réseau** (Download / Upload avec historique)
- 🔋 **Batterie**
- 💾 **Stockage**

### 📊 Affichage
- Mode **nCurses** avec graphiques temps réel
- Histogrammes et barres dynamiques
- Échelles automatiques
- Mode **SFML** (graphique)
- Déplacement des fenêtres

---

## 🏗️ Architecture

Le projet repose sur deux interfaces principales :

- `Krell::IModule` : représente un module système
- `Krell::IDisplay` : représente un mode d’affichage

Cette conception garantit modularité, extensibilité et clarté du code.

---

## 🚀 Compilation & Lancement

### 🔧 Compilation
```bash
make
```

### ▶️ Lancement
```bash
./MyGKrellm
```

---

## ⌨️ Contrôles

| Touche | Action   |
|------|-------                            |
| `q` | Quitter                            |
| `s` | Changer de mode                    |
| `↑ / ↓` | Navigation modules             |
| `1, 2, ..0` | visibilité du Nième module |

---

## ⚠️ Contraintes techniques

- Langage : **C++**
- Fonctions interdites :
  - `malloc`, `free`
  - `printf`
  - `open`, `fopen`
  - `using namespace`
- Gestion mémoire propre
- Pas de droits administrateur requis

---

## 🌟 Bonus

- Graphiques dynamiques
- Historique temporel
- Interface ergonomique

---

## 👨‍💻 Auteurs

Projet réalisé dans le cadre du **RUSH 4 – Epitech**

- 👨‍💻 Leo Batilliot — [@Leo-Batilliot](https://github.com/Leo-Batilliot)
- 👨‍💻 Clement Dujardin Duribreux — [@Clement-DujardinDuribreux](https://github.com/Clement-DujardinDuribreux)
- 👨‍💻 Thomas Berroy — [@ThomasBerroy](https://github.com/ThomasBerroy)
- 👨‍💻 Florent Windels — [@FloWindels](https://github.com/FloWindels)

---

> *Simple, modulaire, efficace.*
