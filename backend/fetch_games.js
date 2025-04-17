// adapted from Axios documentation for performing GET requests https://axios-http.com/docs/example
// and the Node.js fs module for writing to files https://nodejs.org/api/fs.html#fswritefilesyncfile-data-options 

const axios = require('axios');
const fs = require('fs');

async function fetchGames() {
    try {
        const response = await axios.get('https://bridgesdata.herokuapp.com/api/games');
        const games = response.data.data; // data is nested under 'data' key
        // save to a JSON file for C++ to read
        fs.writeFileSync('games.json', JSON.stringify(games, null, 2));
        console.log(`Fetched ${games.length} games and saved to games.json`);
    } catch (error) {
        console.error('Error fetching games:', error.message);
    }
}

fetchGames();