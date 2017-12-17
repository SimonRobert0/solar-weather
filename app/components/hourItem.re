open BsReactNative;

let component = ReasonReact.statelessComponent("HourItem");

open MomentRe;

[@bs.raw "require('moment-timezone)"];

[@bs.send] external tz : (Moment.t, string) => Moment.t = "tz";

let styles =
  StyleSheet.create(
    Style.(
      {
        "hour": style([width(Pct(7.65)), alignItems(Center), height(Pct(100.))]),
        "hourText":
          style([
            textAlign(Center),
            fontWeight(`_600),
            color("#EFEFEF"),
            marginTop(Pt(15.))
          ]),
        "image":
          style([
            alignSelf(Center),
            width(Pct(90.)),
            marginTop(Pt((-5.))),
            resizeMode(Contain)
          ]),
        "temperature": style([color("#EFEFEF"), fontSize(14.)])
      }
    )
  );

let make =
    (
      ~unit,
      ~timeType,
      ~temperature: float,
      ~icon: string,
      ~timezone,
      ~time,
      _children
    ) => {
  ...component,
  render: (_self) => {
    let temperature =
      unit === "c" ?
        Temperature.fixTemperature(temperature) :
        Temperature.convertToFahrenheitAndFix(temperature);
    let formatString = timeType === "24" ? "HH:mm" : "h:mma";
    let date =
      tz(momentWithUnix(time), timezone)
      |> Moment.startOf(`minute)
      |> Moment.format(formatString);
    let icon = Icons.identifyIcon(icon ++ "_white");
    let iconSource: Image.imageSource =
      switch icon {
      | None =>
        Image.(
          Required(
            Packager.require("../../../../assets/weather_icons/sunny.png")
          )
        )
      | Some(image) => image
      };
    <View style=styles##hour key=date>
      <Text style=styles##hourText> (ReasonReact.stringToElement(date)) </Text>
      <WeatherIconWrapper>
        <Image style=styles##image source=iconSource />
      </WeatherIconWrapper>
      <Text style=styles##temperature>
        (ReasonReact.stringToElement(temperature ++ "\176"))
      </Text>
    </View>
  }
};

let default =
  ReasonReact.wrapReasonForJs(
    ~component,
    (jsProps) =>
      make(
        ~unit=jsProps##unit,
        ~timeType=jsProps##timeType,
        ~temperature=jsProps##temperature,
        ~icon=jsProps##icon,
        ~timezone=jsProps##timezone,
        ~time=jsProps##time,
        [||]
      )
  );