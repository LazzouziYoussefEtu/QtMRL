
# QtMRL — Qt Moniteur de Ressources Linux

**QtMRL** est une application graphique développée en C++ avec Qt 6, conçue pour surveiller les ressources système sous Linux en temps réel. L’application fournit une interface claire avec des graphiques dynamiques pour observer l’utilisation du CPU, de la RAM, et la puissance du signal WiFi.

---

## 📌 Objectifs

- Offrir une interface moderne et fluide pour surveiller les performances du système.
- Visualiser en temps réel :
  - la puissance du signal WiFi,
  - l'utilisation de la mémoire vive (RAM),
  - l'activité du processeur (CPU).
- Étendre vers un moniteur complet (swap, processus, réseau...).

---

## ⚙️ Techniques utilisées

- **Langage** : C++
- **Framework** : Qt 6 (Widgets, Charts, QTimer, QProcess, QRegularExpression)
- **Outils Linux** : `iwconfig`, `free`, `top` ou `/proc/stat`
- **Modules Qt** :
  - `QChartView`, `QLineSeries`, `QTimer`, `QProcess`
  - `QValueAxis` pour personnaliser les axes
  - `QRegularExpression` pour parser les sorties shell

---

## 📊 Fonctionnalités actuelles

### 📶 Signal WiFi (classe `WifiSignalChart`)
- Détection automatique de l’interface sans-fil active (`detectWifiInterface()`).
- Extraction du niveau du signal via `iwconfig` (`getSignalStrength()`).
- Mise à jour toutes les secondes du graphique (`updateChart()`).

### 💾 Utilisation de la RAM (classe `RamUsageChart`)
- Exécution de la commande `free -m` pour obtenir la mémoire utilisée.
- Extraction de la mémoire utilisée par rapport à la mémoire totale.
- Affichage en temps réel avec une ligne de progression dynamique.

### 🧠 Activité CPU (classe `CpuUsageChart`)
- Lecture des données depuis `/proc/stat`.
- Calcul de l'utilisation active du CPU à chaque seconde.
- Affichage en ligne du taux d'occupation du processeur.

---

## 📁 Structure du projet

```
QtMRL/
├── README.md
├── main.cpp
├── includes
│   ├── cpuusagechart.h
│   ├── ramusagechart.h
│   └── wifisignalchart.h
└── src
    ├── cpuusagechart.cpp
    ├── ramusagechart.cpp
    └── wifisignalchart.cpp
```


## 🧪 Compilation

Assure-toi d’avoir **Qt 6** installé avec `qmake` et `make` :

```bash
git clone https://github.com/LazzouziYoussefEtu/QtMRL
cd QtMRL
qmake && make
./QtMRL
```

---

## 👨‍💻 Auteur

Développé par **Youssef Lazzouzi**  
🔗 GitHub : [LazzouziYoussefEtu](https://github.com/LazzouziYoussefEtu)

---

## 📜 Licence

Ce projet est open-source sous licence MIT
