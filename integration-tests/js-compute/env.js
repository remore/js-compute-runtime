export function getEnv(serviceName) {
  return {
    DICTIONARY_NAME: `aZ2__2${serviceName ? '__' + serviceName.replace(/-/g, '_') : ''}`,
    CONFIG_STORE_NAME: `testconfig${serviceName ? '__' + serviceName.replace(/-/g, '_') : ''}`,
    KV_STORE_NAME: `example-test-kv-store${serviceName ? '--' + serviceName : ''}`,
    SECRET_STORE_NAME: `example-test-secret-store${serviceName ? '--' + serviceName : ''}`,
    ACL_NAME: `exampleacl${serviceName ? '__' + serviceName.replace(/-/g, '_') : ''}`,
  };
}
