To add a shader, first make a folder with your shader name
then make two files "fragment.shader" and "vertex.shader"
you can use the "Main" folder as an example
then, in the code, to add your shader make a new shader,
here an example with our "Main" folder:
{
	//You just need to put the folder name, not the path
	Shader mShader("Main");

	//Add this with the other unBinds before the main loop
	mShader.UnBind();

	//On main loop
	renderer.RenderScene(va, ib, mShader);
}

so, if you want to edit an uniform, you need to add this code line ( if it will change on running time, add this before  the "RenderScene" function):
{
	//float can be any other type of uniform variables, like: Vec3, float, int, etc...
	//"uName" is the name of the uniform
	mShader.setUniform<Float>("uName", 1.0f);
}

and that is it, now you have your shader inside OpenLiv