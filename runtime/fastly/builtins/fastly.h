#ifndef FASTLY_FASTLY_H
#define FASTLY_FASTLY_H

#include "../../StarlingMonkey/builtins/web/url.h"
#include "../host-api/host_api_fastly.h"
#include "./fetch/request-response.h"
#include "builtin.h"
#include "extension-api.h"
#include "fastly.h"
#include "host_api.h"

namespace fastly::fastly {

extern bool DEBUG_LOGGING_ENABLED;
extern bool ENABLE_EXPERIMENTAL_HTTP_CACHE;

class Env : public builtins::BuiltinNoConstructor<Env> {
private:
  static bool env_get(JSContext *cx, unsigned argc, JS::Value *vp);

public:
  static constexpr const char *class_name = "Env";

  static const JSFunctionSpec static_methods[];
  static const JSPropertySpec static_properties[];
  static const JSFunctionSpec methods[];
  static const JSPropertySpec properties[];

  static JSObject *create(JSContext *cx);
};

class Fastly : public builtins::BuiltinNoConstructor<Fastly> {
private:
  static bool log(JSContext *cx, unsigned argc, JS::Value *vp);

public:
  static constexpr const char *class_name = "Fastly";

  static JS::PersistentRooted<JSObject *> env;
  static JS::PersistentRooted<JSObject *> baseURL;
  static JS::PersistentRooted<JSString *> defaultBackend;
  static bool allowDynamicBackends;
  static host_api::BackendConfig defaultDynamicBackendConfig;

  static const JSPropertySpec properties[];

  static bool createFanoutHandoff(JSContext *cx, unsigned argc, JS::Value *vp);
  static bool createWebsocketHandoff(JSContext *cx, unsigned argc, JS::Value *vp);
  static bool now(JSContext *cx, unsigned argc, JS::Value *vp);
  static bool dump(JSContext *cx, unsigned argc, JS::Value *vp);
  static bool enableDebugLogging(JSContext *cx, unsigned argc, JS::Value *vp);
  static bool getGeolocationForIpAddress(JSContext *cx, unsigned argc, JS::Value *vp);
  static bool getLogger(JSContext *cx, unsigned argc, JS::Value *vp);
  static bool includeBytes(JSContext *cx, unsigned argc, JS::Value *vp);
  static bool version_get(JSContext *cx, unsigned argc, JS::Value *vp);
  static bool env_get(JSContext *cx, unsigned argc, JS::Value *vp);
  static bool baseURL_get(JSContext *cx, unsigned argc, JS::Value *vp);
  static bool baseURL_set(JSContext *cx, unsigned argc, JS::Value *vp);
  static bool defaultBackend_get(JSContext *cx, unsigned argc, JS::Value *vp);
  static bool defaultBackend_set(JSContext *cx, unsigned argc, JS::Value *vp);
  static bool allowDynamicBackends_get(JSContext *cx, unsigned argc, JS::Value *vp);
  static bool allowDynamicBackends_set(JSContext *cx, unsigned argc, JS::Value *vp);
};

JS::Result<std::tuple<JS::UniqueChars, size_t>> convertBodyInit(JSContext *cx,
                                                                JS::HandleValue bodyInit);

/**
 * Debug only logging system, adding messages to `fastly.debugMessages`
 *
 * This is useful for debugging compute, allowing messages to be inlined into the response in test
 * case debugging, where other logging systems may introduce greater latency than this.
 */

} // namespace fastly::fastly

void fastly_push_debug_message(std::string msg);

#endif
