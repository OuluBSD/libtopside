static void InitializeLibrary();
static void UninitializeLibrary();

static void CreateWorld(NativeWorld& world);
static void ClearWorld(NativeWorld& world);
static void SetGravity(NativeWorld& world, float f);
static void SetWorldCFM(NativeWorld& world, float f);
static void SetMaxCorrectingVelocity(NativeWorld& world, float f);
static void SetContactSurfaceLayer(NativeWorld& world, float f);
static void SetAutoDisable(NativeWorld& world, bool b);
static void SetStepIterations(NativeWorld& world, int i);
static void SetAutoDisableSamples(NativeWorld& world, int i);

static void CreateSpace(NativeSpace& space, bool is_root);
static void ClearSpace(NativeSpace& space);
static void Collide(NativeSpace& space, void* data, NearCallback cb);
static void Step(NativeWorld& world, float seconds);

static void CreateJointGroup(NativeJointGroup& g);
static void ClearJointGroup(NativeJointGroup& g);
static void DetachJointGroup(NativeJointGroup& g);

static void CreateThreading(NativeThreading& t);
static void CreateThreadPool(NativeThreadPool& p);
static void AttachThreadPool(NativeThreading& t, NativeThreadPool& p);
static void AttachThreading(NativeWorld& w, NativeThreading& t);
static void DetachThreading(NativeWorld& w);
static void DetachThreading(NativeThreading& t);
static void ClearThreadPool(NativeThreadPool& p);
static void ClearThreading(NativeThreading& t);

static NativeBody CreateBody(NativeWorld w);
static vec3 GetBodyPosition(NativeBody b);
static void SetBodyPosition(NativeBody b, float x, float y, float z);

static void SetGeomPosition(NativeGeom g, float x, float y, float z);
static void SetGeomRotationAxisAngle(NativeGeom geom, float ax, float ay, float az, float angle);
static void ResetGeomRotation(NativeGeom geom);

static NativeJoint CreateJointHinge2(NativeWorld w);
static void AttachJoint(NativeJoint& j, NativeBody& b0, NativeBody& b1);
static NativeQuat GetDefaultOrientation();
static void SetJointFeedback(NativeJoint j, NativeFeedback& fb);
static void SetJointHingeAnchor(NativeJoint& j, const vec3& pos);
static void SetJointHingeAxes(NativeJoint& j, const vec3& axis1, const vec3& axis2);
static void SetSuspensionERP(NativeJoint& j, float erp);
static void SetSuspensionCFM(NativeJoint& j, float cfm);
static void SetHingeRange(NativeJoint& j, float lo, float hi, int idx=0);
static void SetHingeVelocity(NativeJoint& j, float v, int idx=0);
static void SetMaxForce(NativeJoint& j, float v, int idx=0);
static void SetFudgeFactor(NativeJoint& j, float v);
static void SetHingeAnchor(NativeJoint& j, const vec3& v);
static void SetAxis(NativeJoint& j, const vec3& v);
static float GetAngle(NativeJoint& j);