// https://www.geeksforgeeks.org/read-json-file-using-javascript/
// https://developer.mozilla.org/en-US/docs/Web/API/Fetch_API/Using_Fetch
// https://developer.mozilla.org/en-US/docs/Web/API/Document/createElement
function loadHashData() {
    fetch("hash_time.txt")
      .then(response => response.text())
      .then(time => {
        document.getElementById("hashTime").textContent = time;
      });
    fetch("hash_output.json")
      .then(response => response.json())
      .then(games => {
        var container = document.getElementById("gameResults");
        container.innerHTML = "";
        if (games.length === 0) {
          container.innerHTML = "<p>No games found.</p>";
          return;
        }
        // load 5 games
        for (var i = 0; i < games.length && i < 5; i++) {
          var game = games[i];
          var div = document.createElement("div");
          div.classList.add("game-card");
          var html = "<h3>" + game.title + "</h3>";
          html += "<p><strong>Rating:</strong> " + game.rating.toFixed(2) + "</p>";
          html += "<p><strong>Genre:</strong> " + game.genre.join(", ") + "</p>";
          html += "<p><strong>Platform:</strong> " + game.platform + "</p>";
          div.innerHTML = html;
          container.appendChild(div);
        }
      });
  }
  