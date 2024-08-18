const fs = require("fs");
const { join, extname } = require("path");

function count(path) {
  var lines = 0;

  fs.readdirSync(path).map((currentPath) => {
    var currentJoinedPath = join(path, currentPath);
    if (fs.statSync(currentJoinedPath).isFile()) {
      const en = extname(currentPath);
      if (en != ".ino" && en != ".cpp" && en != ".hpp") return;

      const linesInFile = fs
        .readFileSync(currentJoinedPath)
        .toString()
        .split("\n").length;
      lines += linesInFile;

      console.log(currentJoinedPath, linesInFile);
    } else {
      lines += count(currentJoinedPath);
    }
  });

  return lines;
}

console.log(count("./"));
