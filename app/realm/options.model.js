import Realm from 'realm';

class Options extends Realm.Object {}
Options.schema = {
  name: 'Options',
  primaryKey: 'key',
  properties: {
    key: { type: 'int' },
    unit: { type: 'string', default: 'c' },
    unitIndex: { type: 'int', default: 0 },
    timeType: { type: 'string', default: '24' },
    timeIndex: { type: 'int', default: 0 },
    locationIndex: { type: 'int', default: 0 },
    onboarding: { type: 'bool', default: false },
  },
};

export default Options;