# QtMRL — Qt Moniteur de Ressources Linux

**QtMRL** est une application graphique développée en C++ avec Qt, permettant de surveiller les ressources système sous Linux. Elle fournit une visualisation en temps réel des signaux tels que la puissance du signal WiFi, l'utilisation de la mémoire, et plus encore (en cours de développement).

---

## 📌 Objectifs

- Fournir une interface fluide et moderne pour surveiller les ressources système.
- Visualiser la puissance du signal WiFi en temps réel (dBm).
- Préparer l'intégration future de l'utilisation du CPU, RAM, swap, processus, etc.

---

## ⚙️ Technologies utilisées

- **C++**
- **Qt 6** (Widgets, Charts, QTimer, QProcess, QRegularExpression)
- **Linux CLI tools** : `iwconfig`, `ifconfig` (en remplacement possible)
- **QChartView** pour les graphiques dynamiques

---

## 📊 Fonctionnalités actuelles

### 📶 Graphique de puissance du signal WiFi

- **Méthodes principales :**
  - `detectWifiInterface()` : détecte automatiquement l'interface sans-fil active.
  - `getSignalStrength(QString interface)` : utilise `iwconfig` pour extraire le signal (niveau en dBm).
  - `updateChart()` : met à jour le graphique avec de nouvelles données toutes les secondes.
  
- **Attributs importants :**
  - `QLineSeries *series` : contient les points à afficher.
  - `QTimer *timer` : déclenche les mises à jour.
  - `int timeStep` : incrément temporel simulant l’axe X.
  - `QString wifiInterface` : nom de l'interface WiFi détectée.

- **Techniques Qt utilisées :**
  - `QChartView` & `QLineSeries` pour le rendu graphique.
  - `QValueAxis` pour personnaliser les axes X et Y.
  - `QRegularExpression` pour extraire les valeurs du signal.
  - `QProcess` pour exécuter des commandes shell.

---

## 📁 Structure du projet (extrait)

```
QtMRL/
├── main.cpp
├── wifisignalchart.h
├── wifisignalchart.cpp
├── QtMRL.pro
└── README.md
```

---

## 🚀 À venir

- Affichage de l'utilisation de la RAM.
- Monitoring CPU et processus.
- Ajout d'icônes système, thème clair/sombre.
- Export des données.

---

## 📦 Compilation

Assure-toi d’avoir Qt 6 installé avec Qt Creator ou `qmake` :
```bash
git clone https://github.com/LazzouziYoussefEtu/QtMRL
cd QtMRL
qmake && make
./QtMRL
```

---

## 🧑‍💻 Auteur

Développé par **Youssef Lazzouzi**  
🔗 GitHub : [LazzouziYoussefEtu](https://github.com/LazzouziYoussefEtu)

---

## 📜 Licence

Projet open-source, sous licence MIT.
