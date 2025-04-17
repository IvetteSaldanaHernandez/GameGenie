fetch("games.json")
    .then(function(response) {
        return response.json();
    })
    .then(function(data) {
        var games = data.data;
        genres = [];
        for (var i = 0; i < games.length; i++) {
            var gameGenres = games[i].genre;
            for (var j = 0; j < gameGenres.length; j++) {
                var genre = gameGenres[j];
                if (genres.indexOf(genre) == -1) {
                    genres.push(genre);
                }
            }
        }
        genres.sort();
        var platforms = [];
        for (var i = 0; i < games.length; i++) {
            var platform = games[i].platform;
            if (platforms.indexOf(platform) === -1) {
              platforms.push(platform);
            }
          }
        platforms.sort();

        var genreSelect = document.getElementById("selectGenre");
        for (var i = 0; i < genres.length; i++) {
            var option = document.createElement("option");
            option.value = genres[i];
            option.textContent = genres[i];
            genreSelect.appendChild(option);
        }

        var platformSelect = document.getElementById("selectPlatform");
        for (var i = 0; i < platforms.length; i++) {
            var option = document.createElement("option");
            option.value = platforms[i];
            option.textContent = platforms[i];
            platformSelect.appendChild(option);
        }
        console.log(genres);
        console.log(platforms);
    })