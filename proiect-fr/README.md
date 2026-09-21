# Brăila, la perle du Danube 🗺️

Carte interactive des monuments de Brăila (projet de français).

## Lancer le site

```bash
npm install
npm start          # → http://localhost:3000
```

`npm run dev` redémarre le serveur à chaque modification.

## Fonctionnalités

- **Carte + itinéraire** : 12 étapes reliées par les vraies rues (à pied dans le centre, en voiture pour le reste)
- **Fiche de chaque lieu** : description, « Le saviez-vous ? », vocabulaire FR → RO en cartes à retourner
- **🔊 Écouter** : le texte est lu à voix haute en français (voix du navigateur)
- **▶ Visite guidée** : parcourt toutes les étapes et lit chaque fiche automatiquement (flèches ← → du clavier aussi)
- **Filtres** par catégorie, **progression** « lieux visités » (mémorisée dans le navigateur)
- **Quiz** de 10 questions (corrigé par le serveur)
- **Lexique** avec tout le vocabulaire et un mode « cacher le roumain » pour réviser
- **Livre d'or** : les visiteurs laissent un commentaire sur chaque lieu (enregistré dans `data/comments.json`)
- **Liens directs** : `http://localhost:3000/#istrati` ouvre directement une fiche

## Modifier le contenu

| Fichier | Contenu |
|---|---|
| `data/landmarks.json` | les lieux (texte, coordonnées, vocabulaire). L'ordre = l'ordre de la visite |
| `data/quiz.json` | les questions (`reponse` = numéro du bon choix, à partir de 0) |

Après avoir ajouté/déplacé un lieu, relancez `npm run build-route` pour recalculer l'itinéraire.

## Structure

```
server.js            serveur Express + API (/api/landmarks, /api/route, /api/quiz, /api/comments)
public/              page web (index.html, style.css, app.js)
data/                contenu en JSON
scripts/build-route.js  calcule l'itinéraire avec OpenStreetMap
```
