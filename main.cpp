#include <iostream>


/*the base state class declares methods that all concrete state should implement and also provides a backreference to the context object,
associated with the state. This backreference can be used by States to transition the context to another state
*/
class Context;
class State{
    protected:
        Context* istContext;
    public:
        virtual ~State(){
        }
        void set_context(Context *context){
            this->istContext=context;
        }
        virtual void Handle1()=0;
        virtual void Handle2()=0;
};

/*The context defines the interface of interest to clients. It also maintains a referefence to an instance of a State subclass, which represents
the current state of the context 
*/

class Context{
    /*reference to the current state of the context */
    private:
        State* itsState;
    public:
        Context(State* state):itsState(nullptr){
            this->TransitionTo(state);
        }
        ~Context() {
            delete itsState;// was deleted initiated with NEW?
        }
        /*the Context allows chaning the state object at runtime*/
        void TransitionTo(State* state){
            std::cout << "Context: Transition to " << typeid(*state).name() << ".\n";
            if(this->itsState!=nullptr){
                delete this->itsState;
            }
            this->itsState=state;
            this->itsState->set_context(this);
        }

        void Request1(){
            this->itsState->Handle1();
        }
        void Request2(){
            this->itsState->Handle2();
        }

};

/*Concrete States implement various behaviours, associated with a state of the context*/
//class ConcreteStateB;
class ConcreteStateA: public State{
    public:
        void Handle1() override;
        //      std::cout<<"A handles request 1 "<<std::endl;
        //      std::cout<<"A wants to change the state of the context"<<std::endl;
        //      this->istContext->TransitionTo(new ConcreteStateB);
        // }
        void Handle2() override{
            std::cout<<" A: handles request 2"<< std::endl;
        }
};

class ConcreteStateB: public State{
    public:
        void Handle1() override{
            std::cout<<" B: handles request 1"<<std::endl;
        }
        void Handle2() override{
            std::cout<<" B: handles request 2"<<std::endl;
            std::cout<<" B: changes to state A "<<std::endl;
            this->istContext->TransitionTo(new ConcreteStateA);
        }
};


void ConcreteStateA::Handle1(){
    std::cout<<" A: handles request 1"<<std::endl;
    std::cout<<" A: changes to state B "<<std::endl;
    this->istContext->TransitionTo(new ConcreteStateB);
}

int main()
{
    Context* itsContext = new Context(new ConcreteStateA);
    itsContext->Request1(); // switching to B
    itsContext->Request2(); // switchinb back to A
    //std::cout<<" hello world "<< std::endl;
    return 0;  

}