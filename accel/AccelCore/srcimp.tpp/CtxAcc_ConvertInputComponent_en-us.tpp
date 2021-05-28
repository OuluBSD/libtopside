topic "";
[H6;0 $$1,0#05600065144404261032431302351956:begin]
[i448;a25;kKO9;2 $$2,0#37138531426314131252341829483370:codeitem]
[l288;2 $$3,0#27521748481378242620020725143825:desc]
[0 $$4,0#96390100711032703541132217272105:end]
[ $$0,0#00000000000000000000000000000000:Default]
[{_} 
[s1; &]
[s2;:Topside`:`:ContextAccelT`:`:ConvertInputComponent`:`:LoadAsInput`(const Topside`:`:AcceleratorHeader`&`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 Ctx]>_[@(0.0.255) bool]_ContextAccelT<[*@4 Ctx]>`::_Conv
ertInputComponent`::LoadAsInput([@(0.0.255) const]_AcceleratorHeader[@(0.0.255) `&]_[*@3 i
n])&]
[s3;%%  [%-*@3 in] is a read`-only`-reference to the information object, 
that contains the description of the data what the accelerator 
component expects to read.&]
[s0;%% &]
[s0;%% Simplified example of this function would be like like imaginary 
self`-explanatory function doing:&]
[s0;i150;O0; [%% Context function is calling: ClassWhichLoadsTextureToOpenGLStage 
`:: ]LoadAsInput (const InfoForLoader`& in)&]
[s0;i150;O0; Function: finds existing loader component or creates 
a new component (with the class LoadsTextureFile)&]
[s0;i150;O0;%% [%- LoadsTextureFile component is connected to ]ClassWhichLoadsTextureTo
OpenGLStage component&]
[s0;i150;O0; [%% We get the TextureStream from ]LoadsTextureFile and 
ask it to load the file from the path in InfoForLoader&]
[s0;i150;O0; We expect the system to update stream, which push the 
texture eventually to the OpenGL stage once.]]