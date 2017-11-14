// Modules
import React, { PureComponent } from 'react';
import PropTypes from 'prop-types';

import {
  StyleSheet,
  Animated,
  ListView,
  Dimensions,
} from 'react-native';

// Components
import HourItem from './HourItem.component';

export default class HourForecast extends PureComponent { // eslint-disable-line
  constructor(props) {
    super(props);
    const ds = new ListView.DataSource({ rowHasChanged: (r1, r2) => r1 !== r2 });
    this.state = {
      dataSource: ds.cloneWithRows([]),
      bottomAnim: new Animated.Value(-Dimensions.get('window').height / 10),
    };
  }

  componentWillReceiveProps(nextProps) {
    const { openHours, anyLocation } = this.props;
    if (nextProps.openHours !== openHours && anyLocation) {
      this.animateBottom();
    }
    if (nextProps.locationName !== this.props.locationName) {
      _scrollView.scrollTo({ x: 0, y: 0, animated: true });
    }
    if (nextProps.forecast !== this.props.forecast) {
      this.setState({
        dataSource: this.state.dataSource.cloneWithRows(nextProps.forecast),
      });
    }
  }

  animateBottom() {
    const bottomValue = this.props.openHours ?
      -Dimensions.get('window').height / 10 : Dimensions.get('window').height / 10;
    Animated.timing(
      this.state.bottomAnim,
      { toValue: bottomValue },
    ).start();
  }

  render() {
    const { timeType, unit, timezone } = this.props;
    return (
      <Animated.View
        style={{
          position: 'absolute',
          width: '100%',
          height: '20%',
          left: 0,
          flex: 1,
          bottom: this.state.bottomAnim,
        }}
      >
        <ListView
          ref={(scrollView) => { _scrollView = scrollView; }}
          horizontal
          pagingEnabled
          style={{ flex: 1 }}
          contentContainerStyle={styles.container}
          enableEmptySections
          showsHorizontalScrollIndicator={false}
          bounces={false}
          directionalLockEnabled
          dataSource={this.state.dataSource}
          renderRow={(rowData, secId, rowId) => (
            <HourItem
              {...rowData}
              unit={unit}
              timeType={timeType}
              timezone={timezone}
              rowId={rowId}
            />
          )}
        />
      </Animated.View>
    );
  }
}

HourForecast.propTypes = {
  forecast: PropTypes.arrayOf(PropTypes.shape({})),
  openHours: PropTypes.bool,
  timeType: PropTypes.string,
  unit: PropTypes.string,
  timezone: PropTypes.string,
  anyLocation: PropTypes.bool,
};

const styles = StyleSheet.create({
  container: {
    minWidth: '250%',
    flex: 1,
    alignItems: 'center',
    flexDirection: 'row',
    height: '100%',
    backgroundColor: 'rgba(0, 0, 0, 0.1)',
    position: 'relative',
  },
});