
#define TRANSFORM_EPSILON .00001f

void
InitTransform(transform* Transform)
{
	Transform->Position = v3(0,0,0);
	Transform->Rotation = quat(1,0,0,0);
	Transform->Scale = v3(1,1,1);
}

transform
CombineTransforms(transform* First, transform* Second)
{
	transform Out;
	Out.Rotation = First->Rotation * Second->Rotation;
	Out.Scale = First->Scale * Second->Scale;
	
	v3 Translation = First->Rotation * (First->Scale * Second->Position);
	Out.Position = First->Position + Translation;
	return Out;
}

transform
InvertTransform(transform* In)
{
	transform Out;
	Out.Rotation = glm::inverse(In->Rotation);
	
	Out.Scale.x = fabs(In->Scale.x) < TRANSFORM_EPSILON ? 0.0f : 1.0f / In->Scale.x;
	Out.Scale.y = fabs(In->Scale.y) < TRANSFORM_EPSILON ? 0.0f : 1.0f / In->Scale.y;
	Out.Scale.z = fabs(In->Scale.z) < TRANSFORM_EPSILON ? 0.0f : 1.0f / In->Scale.z;
	
	v3 InvTranslation = In->Position * -1.0f;
	Out.Position = Out.Rotation * (Out.Scale * InvTranslation);
	return Out;
}

transform
TransformFromMat4(mat4& In)
{
	transform Out;
	
	Out.Position = v3(In[3][0], In[3][1], In[3][2]);
	Out.Rotation = quat_cast(In);
	mat4 RotScale = mat4
	(
	 In[0][0], In[0][1], In[0][2], 0.0f,
	 In[1][0], In[1][1], In[1][2], 0.0f,
	 In[2][0], In[2][1], In[2][2], 0.0f,
	 0,        0,        0,        1
	 );
	mat4 InvRotMat = mat4(glm::inverse(Out.Rotation));
	mat4 ScaleSkewMat = RotScale * InvRotMat;
	Out.Scale = v3(ScaleSkewMat[0][0], ScaleSkewMat[1][1], ScaleSkewMat[2][2]);
	return Out;
}

mat4
TransformToMat4(transform* In)
{
	v3 X = In->Rotation * v3(1,0,0);
	v3 Y = In->Rotation * v3(0,1,0);
	v3 Z = In->Rotation * v3(0,0,1);
	
	X = X * In->Scale.x;
	Y = Y * In->Scale.y;
	Z = Z * In->Scale.z;
	
	v3 P = In->Position;
	
	return mat4
	(
	 X.x, X.y, X.z, 0.0f,
	 Y.x, Y.y, Y.z, 0.0f,
	 Z.x, Z.y, Z.z, 0.0f,
	 P.x, P.y, P.z, 1.0f
	 );
}