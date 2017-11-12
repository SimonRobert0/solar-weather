import Realm from 'realm';

class Currently extends Realm.Object {}
Currently.schema = {
  name: 'Currently',
  properties: {
    summary: 'string',
    icon: 'string',
    precipIntensity: 'float',
    precipProbability: 'float',
    precipType: { type: 'string', optional: true },
    temperature: 'float',
    humidity: 'float',
    apparentTemperature: 'float',
  },
};

export default Currently;
