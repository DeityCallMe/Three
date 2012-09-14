#include "GUI.h"

#include "Header.h"
using namespace CEGUI;
GUI* GUI::soleGUI=0;
GUI::GUI()
{

}
GUI::~GUI()
{

}
GUI* GUI::InitializeGUI(LPDIRECT3DDEVICE9 lp)
{
	if(lp==0)
		goto ends;
	if(soleGUI!=0)
		goto ends;

	soleGUI=new GUI();
	if(!soleGUI->initialize(lp))
	{
		delete soleGUI;
		soleGUI=0;
	}
ends:
	return soleGUI;
}
bool GUI::initialize(LPDIRECT3DDEVICE9 lp)
{
	Direct3D9Renderer& myRenderer =Direct3D9Renderer::create( lp );
	System::create( myRenderer );


	   DefaultResourceProvider* rp =
        static_cast<DefaultResourceProvider*>
            (System::getSingleton().getResourceProvider());
    
    const char* dataPathPrefix = "D:/CEGUI-0.7.7/CEGUI-0.7.7/datafiles";
    char resourcePath[256];

    // for each resource type, set a resource group directory
    sprintf(resourcePath, "%s/%s", dataPathPrefix, "schemes/");
    rp->setResourceGroupDirectory("schemes", resourcePath);
    sprintf(resourcePath, "%s/%s", dataPathPrefix, "imagesets/");
    rp->setResourceGroupDirectory("imagesets", resourcePath);
    sprintf(resourcePath, "%s/%s", dataPathPrefix, "fonts/");
    rp->setResourceGroupDirectory("fonts", resourcePath);
    sprintf(resourcePath, "%s/%s", dataPathPrefix, "layouts/");
    rp->setResourceGroupDirectory("layouts", resourcePath);
    sprintf(resourcePath, "%s/%s", dataPathPrefix, "looknfeel/");
    rp->setResourceGroupDirectory("looknfeels", resourcePath);
    sprintf(resourcePath, "%s/%s", dataPathPrefix, "lua_scripts/");
    rp->setResourceGroupDirectory("lua_scripts", resourcePath);
    sprintf(resourcePath, "%s/%s", dataPathPrefix, "xml_schemas/");
    rp->setResourceGroupDirectory("schemas", resourcePath);   
    sprintf(resourcePath, "%s/%s", dataPathPrefix, "animations/");
    rp->setResourceGroupDirectory("animations", resourcePath);   

	   // set the default resource groups to be used
    CEGUI::Imageset::setDefaultResourceGroup("imagesets");
    CEGUI::Font::setDefaultResourceGroup("fonts");
    CEGUI::Scheme::setDefaultResourceGroup("schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
    CEGUI::WindowManager::setDefaultResourceGroup("layouts");
    CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
    CEGUI::AnimationManager::setDefaultResourceGroup("animations");
    
    // setup default group for validation schemas
    CEGUI::XMLParser* parser = CEGUI::System::getSingleton().getXMLParser();
    if (parser->isPropertyPresent("SchemaDefaultResourceGroup"))
        parser->setProperty("SchemaDefaultResourceGroup", "schemas");        

	return true;
}
void GUI::renderGUI()
{
	System::getSingleton().renderGUI();
}