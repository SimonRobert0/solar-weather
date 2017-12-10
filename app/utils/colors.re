module Colors = {
  let white = "#FFF";
  let black = "#000";
  let lightGrey = "#EEEEEE";
  let lightOrange = "#F2C992";
  let darkOrange = "#FEC272";
  let lightBlueGrey = "#A5C9D6";
  let darkBlueGrey = "#8093B6";
  let lightMatteBlue = "#A6B6BC";
  let darkMatteBlue = "#7C8FA0";
  let lightBlue = "#94B4BD";
  let darkBlue = "#5B828D";
  let lightBeige = "#CEBA9F";
  let darkBeige = "#A88F70";
  let mattePurple = "#6B7AA7";
  let darkPurple = "#565C71";
  let lightSquash = "#7C718C";
  let darkSquash = "#443E4E";
  let darkGrey = "#757575";
  let subtleGrey = "#EFEFEF";
  let snowGrey = "#C1C7C9";
  let snowWhite = "#DEE3E5";
};

let identifyFontColor = (condition: string) =>
  condition === "snow" ? Colors.darkGrey : Colors.subtleGrey;
