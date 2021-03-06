#ifndef FIREBASE_FIRESTORE_CLIENT_CPP_SRC_ANDROID_WRITE_BATCH_ANDROID_H_
#define FIREBASE_FIRESTORE_CLIENT_CPP_SRC_ANDROID_WRITE_BATCH_ANDROID_H_

#include "firestore/src/android/promise_factory_android.h"
#include "firestore/src/android/wrapper.h"
#include "firestore/src/include/firebase/firestore/document_reference.h"
#include "firestore/src/include/firebase/firestore/map_field_value.h"
#include "firestore/src/include/firebase/firestore/write_batch.h"

namespace firebase {
namespace firestore {

// Each API of WriteBatch that returns a Future needs to define an enum value
// here. For example, a Future-returning method Foo() relies on the enum value
// kFoo. The enum values are used to identify and manage Future in the Firestore
// Future manager.
enum class WriteBatchFn {
  kCommit = 0,
  kCount,  // Must be the last enum value.
};

class WriteBatchInternal : public Wrapper {
 public:
  using ApiType = WriteBatch;

  WriteBatchInternal(FirestoreInternal* firestore, jobject object)
      : Wrapper(firestore, object), promises_(firestore) {}

  void Set(const DocumentReference& document, const MapFieldValue& data,
           const SetOptions& options);

  void Update(const DocumentReference& document, const MapFieldValue& data);

  void Update(const DocumentReference& document, const MapFieldPathValue& data);

  void Delete(const DocumentReference& document);

  Future<void> Commit();

 private:
  friend class FirestoreInternal;

  static bool Initialize(App* app);
  static void Terminate(App* app);

  PromiseFactory<WriteBatchFn> promises_;
};

}  // namespace firestore
}  // namespace firebase

#endif  // FIREBASE_FIRESTORE_CLIENT_CPP_SRC_ANDROID_WRITE_BATCH_ANDROID_H_
