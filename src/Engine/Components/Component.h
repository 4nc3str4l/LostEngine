#pragma once

namespace Lost { namespace Components {

    enum SpecificType 
    {
        Type_Model,
		Type_UIImage
    };

    enum GlobalType
    {
		Type_RenderComponent,
		Type_PhysXComponent,
    };

    class Component
    {
    public:
        Component(SpecificType _componentType);
		virtual ~Component();
        SpecificType specificType;
        GlobalType globalType;
		int id;
        bool isActive;
        
	private:
		static int instanceCounter;
    };

}}

