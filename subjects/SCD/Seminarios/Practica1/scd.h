// *****************************************************************************
// Semaphores and Hoare monitors implementation using C++11 concurrency features.
// both classes implement FIFO order.
//
// (public interface declarations)
// Carlos Ureña, 2016-2021.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// *****************************************************************************

#ifndef SCD_HPP
#define SCD_HPP

#include <random>  // default_random_engine et al.
#include <iostream>
#include <sstream>  // stringstream
#include <mutex>
#include <condition_variable>
#include <cassert>
#include <vector>
#include <map>
#include <thread>  // thread
#include <memory> // shared_ptr, make_shared
#include <deque>

// -----------------------------------------------------------------------------

namespace scd
{

using namespace std ;

// incomplete type declarations, so we can declare pointers to these classes.

class HoareMonitor ;
class FIFOQueue ;
class SemaphoreRepr ;
template<class T> class Call_proxy ;

// ----------------------------------------------------------------------------- 
// register and get calling thread name

void   register_thread_name( const std::string & name );
void   register_thread_name( const std::string & rol, const int num );
string get_thread_name()  ;

// -----------------------------------------------------------------------------
// function template for generating random numbers (between two integer 
// compile-time constants)

template< int min, int max > int aleatorio()
{
  static default_random_engine generador( (random_device())() );
  static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
  return distribucion_uniforme( generador );
}

// *****************************************************************************
//
// Class: Semaphore
//
// Classic semaphore objects with FIFO order
// (it is a reference to a Semaphore implementation object)
// ----------------------------------------------------------------------------

class Semaphore
{
   public:

   // initialization
   Semaphore( unsigned init_value );
   Semaphore( unsigned init_value, const std::string & p_name );

   // explicitly dissallow default constructor
   Semaphore() = delete ;

   // dissallow copy constructor and assignements
   // (cannot 'copy' the state from another existing semaphore,
   //  which may have been already used by threads)
   // this forbids creating semaphores aliases
   Semaphore( const Semaphore & sem ) = delete ;
   void operator = (Semaphore & sem ) = delete ;

   // Move constructor:
   // allows to copy state from a semaphore which is not in use
   // this allows:
   //      Semaphore sem = Semaphore(0) ;
   //      sem_vector.push_back( Semaphore(46) );
   Semaphore( Semaphore && sem ) ;

   // delete...
   ~Semaphore() ;

   // operations (member methods)
   void     sem_wait();
   void     sem_signal() ;

   // operations (non member functions)
   friend inline void sem_wait  ( Semaphore & s ) { s.sem_wait()  ; }
   friend inline void sem_signal( Semaphore & s ) { s.sem_signal(); }

   private:
   SemaphoreRepr * repr = nullptr; // pointer to semaphore implementation

   // debug methods:
   //inline void * get_ptr_repr() { return repr; }
   //int get_value() ;

   // function which can access the private methods
   friend void test_semaforos();

} ; // end class Semaphore


// *****************************************************************************
// Class: CondVar
//
// a class for conditions variables with "urgent wait" semantics on signal
// used in Hoare Monitors (only to be used from  HoareMonitor class)
// These condition variables ensure FIFO order.
// ----------------------------------------------------------------------------

class CondVar
{
   public:

   void     wait();     // unconditionally wait on the underlying thread queue
   void     signal();   // signal operation, with "urgent wait" semantics
   unsigned get_nwt() ; // returns number of threads waiting in the cond.var.

   bool empty() { return get_nwt() == 0 ; }

   // create an un-initialized un-usable condition variable
   CondVar() {};
   
   // --------------------------------------------------------------------------
   private:

   CondVar( HoareMonitor * p_monitor ) ; // private constructor, only to be used from inside monitor implementation
   void check(); // check whether this v.c. has been properly created, abort when not.

   friend class HoareMonitor ; // forward declaration of friend monitor class
   HoareMonitor * monitor = nullptr; // reference to the monitor for this variable
   FIFOQueue *    queue   = nullptr; // underlying FIFOQueue
};


// *****************************************************************************
// Class: HoareMonitor
//
// Base class for classic Hoare-style monitors
// (with "urgent wait" signal semantics and guaranteed FIFO order)
// ----------------------------------------------------------------------------

class HoareMonitor
{
   public:

   // --------------------------------------------------------------------------
   protected:  // methods to be called from derived classes (concrete monitors)

   // constructors and destructor
   HoareMonitor() ;
   HoareMonitor( const std::string & p_name ) ;
   ~HoareMonitor();

   // create a new condition variable in this monitor
   CondVar newCondVar() ;

   // --------------------------------------------------------------------------
   private:

   // allow friend classes to access private parts of this class
   template<typename MonClass> friend class Call_proxy ;
   template<typename MonClass> friend class MRef ;
   friend class CondVar ;

   // true iif any thread is running in the monitor
   bool is_running = false ;

   // lock used to serialize access to any monitor's queue
   // (I mean entry and exit from/to: monitor queue, urgent queue, any cond. var. queue).
   // this is the lock used for all calls to 'condition_variable.wait( lock_guard )'
   // (this is NOT the 'monitor queue', that is below)
   std::mutex access_mutex ;

   // name of this monitor (useful for debugging)
   std::string name = "monitor name not assigned" ;

   // queue for threads waiting to enter the monitor (this IS the 'monitor queue')
   FIFOQueue * enter_queue = nullptr ;

   // queue for threads waiting to re-enter the monitor after a call to 'signal'
   FIFOQueue * urgent_queue = nullptr ; 

   // identifier for thread currently in the monitor (when running==true)
   std::thread::id running_thread_id ;

   // enter and leave the monitor
   void enter();
   void leave();
} ;

// *****************************************************************************
// Class: MRef
//
// Reference to a monitor. All monitors should be accesed through these references
// Implements the "execute around" pattern, as described here:
//
//    Wrapping C++ Member Function Calls.
//    Bjarne Stroustrup
//    The C++ Report, June 2000.
//    http://www.stroustrup.com/wrapper.pdf
//
// -----------------------------------------------------------------------------

template<class MonClass> class MRef
{
   private:
   shared_ptr<MonClass> monPtr ; // shared pointer to the monitor

   public:

   // create a reference from a shared_ptr
   inline MRef( shared_ptr<MonClass>  p_monPtr )
   {
      assert( p_monPtr != nullptr );
      monPtr = p_monPtr ;
   }

   // obtain a call proxy through the dereference operator
   inline Call_proxy<MonClass>  operator -> ()
   {
     assert( monPtr != nullptr );
     return Call_proxy<MonClass>( *monPtr ) ; // acquires mutual exclusion
   }
} ;

// -----------------------------------------------------------------------------
// creation of a monitor reference by using a list of
// actual parameters (the list must match a monitor constructor parameters list)

template< class MonClass, class... Args > inline
MRef<MonClass> Create( Args &&... args )
{
   // equivalent to 'new'
   return MRef<MonClass>( make_shared<MonClass>( args... ) );
}

// *****************************************************************************
// Class Call_proxy<...>
//
// each instance holds a reference to a monitor, 
// It is responsible for calling:
//  * 'monitor.enter' (on constructor) and 
//  * 'monitor.leave' (on destruction)
// -----------------------------------------------------------------------------

template<class MonClass> class Call_proxy
{
   private:
   MonClass & monRef ; // monitor reference

   public:
   inline Call_proxy( MonClass & mr ) : monRef(mr) { monRef.enter(); }
   inline MonClass * operator -> () { return &monRef; }
   inline ~Call_proxy() { monRef.leave(); }
};

} // namespace HW end

// *****************************************************************************

#endif // ifndef SCD_HPP
