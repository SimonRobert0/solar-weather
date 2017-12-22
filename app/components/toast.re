open BsReactNative;

let easeIn = (x) => x *. x *. x;

type state = {topAnim: Animated.Value.t};

type retainedProps = {
  error: string,
  displayError: Js.boolean,
  connected: Js.boolean
};

let component = ReasonReact.reducerComponentWithRetainedProps("Toast");

let windowWidth = float_of_int(Dimensions.get(`window)##width);

let styles =
  StyleSheet.create(
    Style.(
      {
        "container":
          style([
            position(Absolute),
            zIndex(3),
            left(Pt(0.)),
            padding(Pt(15.)),
            backgroundColor(Config.AppColors.red),
            width(Pt(windowWidth)),
            height(Pt(50.))
          ]),
        "text":
          style([
            textAlign(Center),
            color(Config.AppColors.white),
            fontWeight(`_700),
            fontFamily("HelveticaNeue")
          ])
      }
    )
  );

let animateToast = (topAnim, toValue) =>
  Animated.CompositeAnimation.start(
    Animated.Timing.animate(
      ~value=topAnim,
      ~toValue=`raw(toValue),
      ~easing=easeIn,
      ()
    ),
    ()
  );

let make =
    (
      ~error: string,
      ~displayError: Js.boolean,
      ~connected: Js.boolean,
      _children
    ) => {
  ...component,
  initialState: () => {topAnim: Animated.Value.create((-100.))},
  retainedProps: {error, displayError, connected},
  reducer: ((), _) => ReasonReact.NoUpdate,
  willReceiveProps: ({state}) =>
    if (Js.to_bool(displayError)) {
      animateToast(state.topAnim, 0.);
      Js.Global.setTimeout(() => animateToast(state.topAnim, (-100.)), 5000);
      state
    } else {
      state
    },
  render: ({state}) =>
    <Animated.View
      style=Style.(
              concat([
                styles##container,
                style([top(Animated(state.topAnim))])
              ])
            )>
      <Text style=styles##text> (ReasonReact.stringToElement(error)) </Text>
    </Animated.View>
};

let default =
  ReasonReact.wrapReasonForJs(
    ~component,
    (jsProps) =>
      make(
        ~error=jsProps##error,
        ~displayError=jsProps##displayError,
        ~connected=jsProps##connected,
        [||]
      )
  );
