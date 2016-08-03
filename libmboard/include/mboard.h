/* $Id: mboard.h 2178 2009-10-01 11:20:41Z lsc $ */
/*!
 * \file mboard.h
 * \code
 *      Author: Lee-Shawn Chin 
 *      Date  : August 2009 
 *      Copyright (c) 2009 STFC Rutherford Appleton Laboratory
 * \endcode
 * 
 * \brief This should be the only header file that has to 
 *        be included by libmboard users
 * \warning This library is designed to work only on homogenous systems
 * 
 * 
 */
#ifndef MBOARD_H_
#define MBOARD_H_

/*!
 * \mainpage libmboard (Message Board Library)
 * 
 * \section OVERVIEW Overview
 * The Message Board Library provides memory management and message data
 * synchronisation facilities for multi-agent simulations generated using the 
 * FLAME framework (http://www.flame.ac.uk). 
 * 
 * \image html mboard_flame.png
 * \image latex mboard_flame.eps "Message Board Library" width=10cm
 * 
 * As agents only interact with its environment (and each other) via messages, 
 * the Message Board library serves as a means of achieving parallelisation. 
 * Agents can be farmed out across multiple processors and simulated 
 * concurrently, while a coherent simulation is maintained through a unified 
 * view of the distributed Message Boards.
 * 
 * Synchronisation of the message boards are non-blocking as they are 
 * performed on a separate communication thread, allowing much of the 
 * communication time to be overlapped with computation.
 * 
 * 
 * \ifnot userdoc
 * - \ref todo
 * \else
 * 
 * \section SOURCE Obtaining the source
 * 
 * You can download the latest release from CCPForge 
 * (http://ccpforge.cse.rl.ac.uk/frs/?group_id=8). We currently only provide
 * private releases, so you will need to be logged in as a member of the 
 * FLAME framework project.
 * 
 * \subsection SOURCE_DEVEL Developers and maintainers
 * 
 * If you are a developer and wish to use the development version (unstable), 
 * you can check out a copy from SVN (http://ccpforge.cse.rl.ac.uk/svn/xagents/trunk/libmboard). 
 * Within the checked out directory, you can either: 
 * -# directly use the maintainer source by running <tt>./autogen.sh</tt> to generate the 
 *    \c Makefiles and \c configure script, or
 * -#  generate your own release file by running <tt>./create_distribution.sh</tt>. 
 *    A \c *.tar.gz file will be generate (and tested). 
 * 
 * 
 * \section INSTALLATION Building and installing the Message Board library
 * 
 * -# Within the source directory, run <tt>"./configure"</tt>. This will configure 
 *    the source code for your system. 
 *  - If you do not have \c root access, or do not wish to install the library 
 *    into the default location (\c /usr/local), you can specify an alternative
 *    location by running <tt>"./configure --prefix=/your/target/dir"</tt> instead. 
 *  - You can also provide further information to the \c configure script as
 *    arguments. Run <tt>"./configure --help"</tt> for a list of possible options.
 * -# Upon successful configuration, run <tt>"make"</tt> to compile the project. 
 * -# (optional) You can run <tt>"make test"</tt> to compile and run the unit
 *    tests. You will need to have CUnit (http://cunit.sourceforge.net/) installed.
 * -# To install your newly built library, run <tt>"make install"</tt>. This 
 *    will install the libraries, header files, and scripts to either the 
 *    default location or the directory you may have specified earlier.
 * 
 * \section USAGE Using the library
 * 
 * To use the Message Board library with your code, you will need to include
 * the mboard.h header file, and call the appropriate \ref FUNC. All Message
 * Board routines return integer-based \ref RC. It is recommended that 
 * you always check the return code, and include sufficient error handling 
 * if the routine ends errorneously.
 * 
 * When linking your executable, you will need to link in the appropriate
 * Message Board library. There are four versions available:
 * - link with <tt>-lmboard_s</tt> for the serial version.
 * - link with <tt>-lmboard_sd</tt> for the serial \b DEBUG version.
 * - link with <tt>-lmboard_p</tt> for the parallel version.
 * - link with <tt>-lmboard_pd</tt> for the parallel \b DEBUG version
 * 
 * Always use the \b DEBUG version during the development and testing
 * stage of your project. They may incur performance overheads, but the \c DEBUG
 * versions include crucial checks and assertions to ensure that the library 
 * is used correctly. 
 * Once your code has been validated and verified, you can switch to the
 * standard version for your production runs.
 * 
 * If your library was installed to a non-default location (by configuring with
 * <tt>"./configure --prefix=/libmboard/install/directory"</tt>), you will need to inform
 * your compiler/linker where to locate the Message Board libraries and header
 * files.
 * - append '<tt>-I/libmboard/install/directory/<b>include</b></tt>' to 
 *   your compilation flags (\c CFLAGS).
 * - append '<tt>-L/libmboard/install/directory/<b>lib</b></tt>' to 
 *   your linker flags (\c LDFLAGS).
 * 
 * The parallel versions of the library uses \c MPI and \c pthreads. Therefore,
 * you may need additional compilation options or specific compilers when using
 * then with you code. This depends on how your system was set up.
 * 
 * Starting from version 0.1.5, the <tt>mboard-conf</tt> utility is provided to
 * assist you in generating the necessary flags for compiling your code with the
 * Message Board library. It will be installed along with your library, and can be
 * found in <tt><i>/libmboard/install/directory/</i>bin</tt>.
 * 
 * Example:
 * - <tt>gcc 'mboard-config --cflags'  -c test.c</tt>
 * - <tt>gcc 'mboard-config --ldflags' -o program test.o 'mboard-config --libs'</tt>
 * 
 * Run <tt>'<i>/libmboard/install/directory/</i>mboard-config --help'</tt> for more details.
 * 
 * \section TUNING Tuning
 * 
 * To tune the behaviour of libmboard, see \subpage tuning.
 * 
 * \section EXAMPLE Example
 * 
 * The <tt>./example/circle_mb</tt> directory within the source contains an example 
 * of how libmboard can be used within a project.
 * 
 * \endif
 */

/*!\ifnot userdoc 
 * \defgroup MB_API Message Board API
 * 
 * Message Board routines exposed to users.
 * \endif
 */
/*!\if userdoc 
 * \defgroup FUNC Message Board API Routines
 * 
 * Routines to create and use Message Boards
 * \endif
 */
/*!\if userdoc 
 * \defgroup  RC Return Codes
 * 
 * All Message Board routines return an <tt>int</tt>-based return code. 
 * It is recommended that users always check the return code of all 
 * routine calls, and include sufficient error handling if the routine
 * ends errorneously.
 * 
 * The following is a list of possible return codes and their description.
 * \endif
 */
/*!\if userdoc 
 * \defgroup DT Datatypes
 * 
 * The following is a list datatypes defined in libmboard. These datatypes
 * are used to hold <i>Handles</i> to opaque objects that can be used for
 * interating with the Message Board library.
 *  
 * \endif
 */
/*!\if userdoc 
 * \defgroup CONST Constants
 * 
 * The following is a list constants defined in libmboard.
 * \endif
 */

#include <stddef.h>
#include <limits.h>
#include "mb_objmap.h"
#include "mb_memlog.h"

/*! 
 * \var MBt_handle
 * \ingroup MB_API
 * \brief Mapping of opaque object handle to internal representation
 */
typedef OM_key_t MBt_handle; 

/* ========== DATATYPES ========== */

/*!
 * \var MBt_Board
 * \ingroup MB_API
 * \ingroup DT
 * \brief A handle to reference Message Board objects
 * 
 * Boards are objects that store messages. A board can be created (using
 * ::MB_Create()) to store data structures of arbitrary type. To store 
 * messages/data of different types, you will need to create diffent 
 * Boards.
 * 
 * Once a board is created, it will remain valid until it is deleted using
 * ::MB_Delete(). It can also be emptied/cleared using ::MB_Clear().
 * 
 * Messages can be added to the Board using ::MB_AddMessage(). However, 
 * messages can only be accessed through Iterators (see 
 * ::MB_Iterator_Create()).
 * 
 * When working in a parallel environment, a unified view of the Message 
 * Board will only be available after it has been synchronised. See:
 * - ::MB_SyncStart()
 * - ::MB_SyncComplete()
 * - ::MB_SyncTest()
 * 
 * \par See also:
 * - ::MB_NULL_MBOARD
 */
typedef MBt_handle MBt_Board;

/*!
 * \var MBt_Iterator
 * \ingroup MB_API
 * \ingroup DT
 * \brief A handle to reference Iterator objects
 * 
 * Iterators are objects that allow users to traverse the contents of a
 * Message Board (::MBt_Board). Iterators can be created from a valid 
 * board using the following routines:
 * 
 * - ::MB_Iterator_Create()
 * - ::MB_Iterator_CreateFiltered()
 * - ::MB_Iterator_CreateSorted()
 * - ::MB_Iterator_CreateFilteredSorted()
 * 
 * Once an Iterator is created, it will remain valid as long as the corresponding
 * board remains intact, and until it is deleted using ::MB_Iterator_Delete().
 * 
 * Messages can be read from Iterators by making repeated calls to 
 * ::MB_Iterator_GetMessage().
 * 
 * \par See also:
 * - ::MB_NULL_ITERATOR
 * - ::MB_Iterator_Rewind()
 * - ::MB_Iterator_Randomise() 
 * 
 */
typedef MBt_handle MBt_Iterator;

/*!
 * \var MBt_Function
 * \ingroup MB_API
 * \ingroup DT
 * \brief A handle to reference Registered Functions
 * 
 * Registered Functions are objects that represent user functions that have
 * been registered with the Message Board Library using 
 * ::MB_Function_Register(). 
 * 
 * This registration provides a unique handle to the function that is 
 * recognised across all processing nodes and can therefore be passed on as 
 * filter functions to ::MB_Function_Assign().
 * 
 * The Registered Function is valid until it is freed using 
 * ::MB_Function_Free().
 * 
 * \par See also:
 * - ::MB_NULL_FUNCTION
 * 
 */
typedef MBt_handle MBt_Function;

/*!
 * \var MBt_Filter
 * \ingroup MB_API
 * \ingroup DT
 * \brief A handle to reference Registered Filter
 * 
 * Filters are objects that represent user functions that have
 * been registered with the Message Board Library using 
 * ::MB_Filter_Create(). 
 * 
 * This registration provides a unique handle to the function that is 
 * recognised across all processing nodes and can therefore be passed on as 
 * filter functions to boards using ::MB_Fitler_Assign().
 * 
 * The Registered Function is valid until it is deleted using 
 * ::MB_Filter_Delete().
 * 
 * \par See also:
 * - ::MB_NULL_FILTER
 * 
 */
typedef MBt_handle MBt_Filter;

/*!
 * \var MBt_IndexMap
 * \ingroup MB_API
 * \ingroup DT
 * \brief A handle to reference Index Map objects
 * 
 * IndexMaps are objects representing a distributed lookup table created using 
 * ::MB_IndexMap_Create(). 
 * 
 * This registration provides a unique handle to the function that is 
 * recognised across all processing nodes and can therefore be in filters
 * assigned to boards.
 * 
 * The Index Map is valid until it is freed using 
 * ::MB_IndexMap_Delete().
 * 
 * \par See also:
 * - ::MB_NULL_INDEXMAP
 * 
 */
typedef MBt_handle MBt_IndexMap;

/* ========== User Routines ========== */

/* Initialise libmboard environment */
int MB_Env_Init(void);

/* Terminate libmboard environment */
int MB_Env_Finalise(void);

/* Indicate whether MPI_Env_Init has been called */
int MB_Env_Initialised(void);

/* Indicate whether MPI_Env_Finalised has been called */
int MB_Env_Finalised(void);

/* Create a new message board */
int MB_Create(MBt_Board *mb_ptr, size_t msgsize);

/* Set access mode of message board */
int MB_SetAccessMode(MBt_Board mb, int MODE);

/* Set read pattern for message board syncs */
int MB_SetSyncPattern(MBt_Board mb, unsigned int *sync_matrix);

/* Add message to board */
int MB_AddMessage(MBt_Board mb, void *msg);

/* Clear all messages in board */
int MB_Clear (MBt_Board mb);

/* Delete board and free allocated memory */
int MB_Delete(MBt_Board *mb_ptr);

/* Create a message iterator */
int MB_Iterator_Create(MBt_Board mb, MBt_Iterator *itr_ptr);

/* Create a sorted message iterator */
int MB_Iterator_CreateSorted(MBt_Board mb, MBt_Iterator *itr_ptr, 
    int (*cmpFunc)(const void *msg1, const void *msg2) );

/* Create a filtered message iterator */
int MB_Iterator_CreateFiltered(MBt_Board mb, MBt_Iterator *itr_ptr, 
        int (*filterFunc)(const void *msg, const void *params), 
        void *filterFuncParams );

/* Create a filtered and sorted message iterator */
int MB_Iterator_CreateFilteredSorted(MBt_Board mb, MBt_Iterator *itr_ptr, 
        int (*filterFunc)(const void *msg, const void *params), 
        void *filterFuncParams, 
        int (*cmpFunc)(const void *msg1, const void *msg2) );

/* Delete an iterator */
int MB_Iterator_Delete(MBt_Iterator *itr_ptr);

/* Get next message from iterator */
int MB_Iterator_GetMessage(MBt_Iterator itr, void **msg_ptr);

/* Rewind Iterator */
int MB_Iterator_Rewind(MBt_Iterator itr);

/* Randomise an Iterator */
int MB_Iterator_Randomise(MBt_Iterator itr);

/* Initiate non-blocking synchronisation of message board */
int MB_SyncStart(MBt_Board mb);

/* Non-blocking routine to test synchronisation completion of message board  */
int MB_SyncTest(MBt_Board mb, int *flag);

/* Complete non-blocking synchronisation of message board */
int MB_SyncComplete(MBt_Board mb);

/* Create a filter */
int MB_Filter_Create(MBt_Filter *fh_ptr, 
        int (*filterFunc)(const void *msg, int pid) );

/* Assign filter to message board */
int MB_Filter_Assign(MBt_Board mb, MBt_Filter fh);

/* Delete a filter */
int MB_Filter_Delete(MBt_Filter *fh_ptr);

/* (DEPRECATED) Register a function */
/*! \brief This function is deprecated. Use MB_Filter_Create() instead */
int MB_Function_Register(MBt_Function *fh_ptr, 
        int (*filterFunc)(const void *msg, const void *params) );

/* (DEPRECATED) Assign function handle to a message board */
/*! \brief This function is deprecated. Use MB_Filter_Assign() instead */
int MB_Function_Assign(MBt_Board mb, MBt_Function fh, 
        void *params, size_t param_size);

/* (DEPRECATED) Deallocate a registered function */
/*! \brief This function is deprecated. Use MB_Filter_Delete() instead */
int MB_Function_Free(MBt_Function *fh_ptr);

/* Create a new Index Map */
int MB_IndexMap_Create(MBt_IndexMap *im_ptr, const char *name);

/* Delete an Index Map */
int MB_IndexMap_Delete(MBt_IndexMap *im_ptr);

/* Add an entry into the map */
int MB_IndexMap_AddEntry(MBt_IndexMap im, int value);

/* Sync map content across processors (blocking collective operation) */
int MB_IndexMap_Sync(MBt_IndexMap im);

/* Determine if a value exists within the map of a specific processor */
int MB_IndexMap_MemberOf(MBt_IndexMap im, int pid, int value);

/* =========== Constants ================= */


/* NULL objects */

/*!
 * \def MB_NULL_MBOARD
 * \ingroup MB_API
 * \ingroup CONST
 * \brief Null Message Board
 * 
 * This value represents an non-existent or invalid Message Board. It
 * is typically returned in place of a Message Board that has been 
 * deleted, or after an erroneous creation of a Message board.
 * 
 */
#define MB_NULL_MBOARD     (MBt_Board)OM_NULL_INDEX

/*!
 * \def MB_NULL_ITERATOR
 * \ingroup MB_API
 * \ingroup CONST
 * \brief Null Iterator
 * 
 * This value represents an non-existent or invalid Iterator object. It
 * is typically returned in place of an Iterator that has been 
 * deleted, or after an erroneous creation of an Iterator.
 * 
 */
#define MB_NULL_ITERATOR   (MBt_Iterator)OM_NULL_INDEX

/*!
 * \def MB_NULL_FUNCTION
 * \ingroup MB_API
 * \ingroup CONST
 * \brief Null Function
 * 
 * This value represents an non-existent or invalid Registered Function. It
 * is typically returned in place of a Registered Function that has been 
 * deleted, or after an erroneous registration of a function.
 */
#define MB_NULL_FUNCTION   (MBt_Function)OM_NULL_INDEX

/*!
 * \def MB_NULL_FILTER
 * \ingroup MB_API
 * \ingroup CONST
 * \brief Null Filter
 * 
 * This value represents an non-existent or invalid Filter object. It
 * is typically returned in place of a Filter that has been 
 * deleted, or after an erroneous registration of a filter function.
 */
#define MB_NULL_FILTER     (MBt_Filter)OM_NULL_INDEX

/*!
 * \def MB_NULL_INDEXMAP
 * \ingroup MB_API
 * \ingroup CONST
 * \brief Null Function
 * 
 * This value represents an non-existent or invalid Index Map. It
 * is typically returned in place of an Index Map that has been 
 * deleted, or after an erroneous creation of a map.
 */
#define MB_NULL_INDEXMAP   (MBt_IndexMap)OM_NULL_INDEX

/* Access Modes */

/*!
 * \def MB_MODE_READWRITE
 * \ingroup MB_API
 * \ingroup CONST
 * \brief Mode: Read-Write
 * 
 * This constant can be used as an input parameter to MB_SetAccessMode().
 * 
 * Specifies that the board is to be treated as a read-write board in 
 * the calling MPI process. Messages can be added to and read from the 
 * board.
 * 
 */
#define MB_MODE_READWRITE   100

/*!
 * \def MB_MODE_READONLY
 * \ingroup MB_API
 * \ingroup CONST
 * \brief Mode: Read-only
 * 
 * This constant can be used as an input parameter to MB_SetAccessMode().
 * 
 * Specifies that the board is to be treated as a read-only board in 
 * the calling MPI process. Messages can be read from the board but
 * not added.
 * 
 */
#define MB_MODE_READONLY    200

/*!
 * \def MB_MODE_WRITEONLY
 * \ingroup MB_API
 * \ingroup CONST
 * \brief Mode: Write-only
 * 
 * This constant can be used as an input parameter to MB_SetAccessMode().
 * 
 * Specifies that the board is to be treated as a write-only board in 
 * the calling MPI process. Messages can be added to the 
 * board but never read locally.
 * 
 */
#define MB_MODE_WRITEONLY   300

/*!
 * \def MB_MODE_IDLE
 * \ingroup MB_API
 * \ingroup CONST
 * \brief Mode: Idle
 * 
 * This constant can be used as an input parameter to MB_SetAccessMode().
 * 
 * Specifies that the board is not used on the calling MPI process. 
 * Messages are never added to or read from the board. 
 * 
 */
#define MB_MODE_IDLE        400

/* boolean */

/*!
 * \def MB_TRUE
 * \ingroup MB_API
 * \ingroup CONST
 * \brief Internal representation of a logical \c TRUE 
 */
#define MB_TRUE 1

/*!
 * \def MB_FALSE
 * \ingroup MB_API
 * \ingroup CONST
 * \brief Internal representation of a logical \c FALSE 
 */
#define MB_FALSE 0

/* ========== RETURN TYPES ========== */

/*!
 * \def MB_SUCCESS
 * \ingroup MB_API
 * \ingroup RC
 * \brief Return Code: Success
 * 
 * Specifies a successful execution.
 */
#define MB_SUCCESS                0

/*!
 * \def MB_ERR_MEMALLOC
 * \ingroup MB_API
 * \ingroup RC
 * \brief Return Code: Memory allocation error
 * 
 * Failed to allocate required memory. We have most likely exhausted all
 * available memory on the system. Use the \c DEBUG version of libmboard
 * for more information on where this occured.
 */
#define MB_ERR_MEMALLOC           1

/*!
 * \def MB_ERR_INVALID
 * \ingroup MB_API
 * \ingroup RC
 * \brief Return Code: Input error
 * 
 * One or more of the given input parameter is invalid. 
 */
#define MB_ERR_INVALID            2 

/*!
 * \def MB_ERR_LOCKED
 * \ingroup MB_API
 * \ingroup RC
 * \brief Return Code: Object locked
 * 
 * Object has being locked by another process.
 */
#define MB_ERR_LOCKED             3 

/*!
 * \def MB_ERR_MPI
 * \ingroup MB_API
 * \ingroup RC
 * \brief Return Code: MPI Error
 * 
 * An MPI related error has occured. Use the \c DEBUG version of libmboard
 * for more information on where this occured.
 */
#define MB_ERR_MPI                4

/*!
 * \def MB_ERR_ENV
 * \ingroup MB_API
 * \ingroup RC
 * \brief Return Code: Environment Error
 * 
 * Specifies error due to uninitalised or invalid environment state. This may
 * be due to users calling Message Board routines before initialising the 
 * environment with ::MB_Env_Init(), or after the environment has been 
 * finalised with ::MB_Env_Finalise().
 */
#define MB_ERR_ENV                5 

/*!
 * \def MB_ERR_OVERFLOW
 * \ingroup MB_API
 * \ingroup RC
 * \brief Return Code: Overflow Error
 * 
 * Specifies error due to an overflow in internal variable or storage.
 * Use the \c DEBUG version of libmboard
 * for more information on where this occured.
 */
#define MB_ERR_OVERFLOW           6

/*!
 * \def MB_ERR_INTERNAL
 * \ingroup MB_API
 * \ingroup RC
 * \brief Return Code: Internal Error
 * 
 * Specifies internal implementation error. Possibly a bug.
 * Use the \c DEBUG version of libmboard
 * for more information on where this occured.
 */
#define MB_ERR_INTERNAL           7

/*!
 * \def MB_ERR_USER
 * \ingroup MB_API
 * \ingroup RC
 * \brief Return Code: User Error
 * 
 * Specifies error due to something the user has done (or not done). See 
 * documentation or any output message for details.
 */
#define MB_ERR_USER               8

/*!
 * \def MB_ERR_NOTREADY
 * \ingroup MB_API
 * \ingroup RC
 * \brief Return Code: Not Ready
 * 
 * The requested operation cannot be completed as the target object is not
 * ready. Refer to the function documentation for details.
 */
#define MB_ERR_NOTREADY           9

/*!
 * \def MB_ERR_DUPLICATE
 * \ingroup MB_API
 * \ingroup RC
 * \brief Return Code: Duplicate value
 * 
 * Duplicate value was entered or found. Refer to function documentaion
 * for details
 */
#define MB_ERR_DUPLICATE          10

/*!
 * \def MB_ERR_NOT_FOUND
 * \ingroup MB_API
 * \ingroup RC
 * \brief Return Code: Required value not found
 * 
 * Refer to function documentaion for details.
 */
#define MB_ERR_NOT_FOUND          11

/*!
 * \def MB_ERR_DISABLED
 * \ingroup MB_API
 * \ingroup RC
 * \brief Return Code: Routine disabled
 * 
 * The requested functionality has been disabled.
 * 
 * Refer to function documentaion for details.
 */
#define MB_ERR_DISABLED           12

/*!
 * \def MB_SUCCESS_2
 * \ingroup MB_API
 * \ingroup RC
 * \brief Return Code: Success 
 * 
 * Specifies a successful execution (but with routine specific connotations).
 */
#define MB_SUCCESS_2              100

/*!
 * \def MB_ERR_NOT_IMPLEMENTED
 * \ingroup MB_API
 * \ingroup RC
 * \brief Return Code: Not Implemented
 * 
 * Requested operation has not been implemented.
 * 
 */
#define MB_ERR_NOT_IMPLEMENTED    111

/*!
 * \def MB_ERR_DEPRECATED
 * \ingroup MB_API
 * \ingroup RC
 * \brief Return Code: Funtion deprecated
 * 
 * The function is deprecated. Please use an alternative function.
 */
#define MB_ERR_DEPRECATED         123


/* =================== BEGIN USER DOCUMENTATION =========================== */
/* -- Doxygen comments below will be used only in the User Documentation -- */

/*!\if userdoc
 * \fn MB_Env_Init(void)
 * \ingroup FUNC
 * \brief Initialises the libmboard environment
 * 
 * This routine must be called before any other libmboard routines 
 * (apart for MB_Env_Initialised() and MB_Env_Finalised()). It launches the 
 * communication thread and initialises all internal data structures required
 * by the library.
 * 
 * The libmboard environment should be initialised only once, and never 
 * re-initialised once it has been finalised (using ::MB_Env_Finalise()).
 * 
 * Possible return codes:
 *  - ::MB_SUCCESS
 *  - ::MB_ERR_MPI (MPI Environment not yet started)
 *  - ::MB_ERR_ENV (libmboard environment already started)
 *  - ::MB_ERR_MEMALLOC (unable to allocate required memory)
 *  - ::MB_ERR_INTERNAL (internal error, possibly a bug)
 * 
 * \endif
 */

/*!\if userdoc
 * \fn MB_Env_Finalise (void)
 * \ingroup FUNC
 * \brief Finalises the libmboard environment
 * 
 * This should be the last libmboard routine called within a program 
 * (apart for MB_Env_Initialised() and MB_Env_Finalised()). It deallocates
 * all internal data structures and terminates the communication thread.
 * 
 * It is erroneous to finalise the environment while there are pending 
 * board synchronisations, i.e. all ::MB_SyncStart() must be completed 
 * with a matching ::MB_SyncComplete() (or successful ::MB_SyncTest()). 
 * 
 * Possible return codes:
 *  - ::MB_SUCCESS
 *  - ::MB_ERR_ENV (libmboard environment not yet started, or already finalised)
 * 
 * \endif
 */

/*!\if userdoc
 * \fn MB_Env_Initialised (void)
 * \ingroup FUNC
 * \brief Indicates whether MB_Env_Init() has been called successfully
 * 
 * This routine will return ::MB_SUCCESS if the environment has been initialised, 
 * or ::MB_ERR_ENV otherwise.
 * 
 *  Possible return codes:
 *  - ::MB_SUCCESS 
 *  - ::MB_ERR_ENV (libmboard environment was not successfully set up, 
 *                 or, has already been finalised)
 * 
 * \endif
 */

/*!\if userdoc
 * \fn MB_Env_Finalised(void)
 * \ingroup FUNC
 * \brief Indicates whether MB_Env_Finalise() has been called
 * 
 * This routine will return ::MB_SUCCESS if the environment has been finalised, 
 * or ::MB_ERR_ENV otherwise.
 * 
 *  Possible return codes:
 *  - ::MB_SUCCESS
 *  - ::MB_ERR_ENV (libmboard environment has not been finalised)
 * 
 * \endif
 */

/*!\if userdoc
 * \fn MB_Create(MBt_Board *mb_ptr, size_t msgsize)
 * \ingroup FUNC
 * \brief Instantiates a new Message Board object
 * \param[out] mb_ptr Address of Message Board handle
 * \param[in] msgsize Size of message that this Message Board will be used for
 * 
 * Creates a new board for storing messages of size \c msgsize and returns a 
 * handle to the board via \c mb_ptr .
 *  
 * In the parallel debug version, this routine is blocking and will return when 
 * all processes have issued and completed the call. This effectively 
 * synchronises all processes. It is the users' responsibility to ensure 
 * that all processes issue the call (with the same values of \c msgsize) 
 * to prevent deadlocks.
 * 
 * If this routine returns with an error, \c mb_ptr will be set to ::MB_NULL_MBOARD.
 * 
 * \note We currently support up to 4096 boards.
 * 
 * Possible return codes:
 *  - ::MB_SUCCESS
 *  - ::MB_ERR_INVALID (\c msgsize is invalid)
 *  - ::MB_ERR_MEMALLOC (unable to allocate required memory)
 *  - ::MB_ERR_OVERFLOW (too many boards created)
 *  - ::MB_ERR_INTERNAL (internal error, possibly a bug)
 *  - ::MB_ERR_ENV (Message Board environment not yet initialised)
 * 
 * Usage example:
 * \include ex_mb_create.c
 * \endif
 */

/*!\if userdoc
 * \fn MB_SetAccessMode(MBt_Board mb, int MODE)
 * \ingroup FUNC
 * \brief Sets access mode of the Message Board
 * \param[in] mb Message Board handle
 * \param[in] MODE Access mode identifier
 * 
 * Sets the access mode of the board to allow the board synchronisation 
 * process to be optimised.
 * 
 * This routine is collective and must be called on all MPI processes.
 * The mode applies only to the calling MPI process hence can be set
 * to a different value on different processes.
 * 
 * When a non-readable mode is set, all \c MB_Iterator_*() will be disabled.
 * Similarly, when a non-writeable mode is set, MB_AddMessage() will 
 * be disabled.
 * 
 * ::MB_MODE_READWRITE is the default mode of all newly created boards.
 * 
 * The following \c MODE values can be used:
 *  - ::MB_MODE_READWRITE - messages will be read and added
 *  - ::MB_MODE_READONLY  - messages will only be read (never added) 
 *  - ::MB_MODE_WRITEONLY - messages will only be added (never read)
 *  - ::MB_MODE_IDLE      - messages will neither be read nor added
 * 
 * This routine can only be called when the message board is empty and
 * not locked.
 * 
 * \warning It is recommended that you never call this routine when there
 * any synchronisation in progress. MB_SetAccessMode() calls MPI routines
 * which may interfere with the synchronisation process if the underlying
 * MPI library is not thread compliant.
 * 
 * Possible return codes:
 *  - ::MB_SUCCESS
 *  - ::MB_ERR_INVALID (\c is null or invalid, or \c MODE is invalid)
 *  - ::MB_ERR_MEMALLOC (unable to allocate required memory)
 *  - ::MB_ERR_LOCKED (\c mb is locked by another process)
 *  - ::MB_ERR_INTERNAL (internal error, possibly a bug)
 *  - ::MB_ERR_MPI (error when calling MPI routines)
 *  - ::MB_ERR_NOTREADY (board is not empty)
 * 
 * Usage example:
 * (to be included)
 * \endif
 */

/*!\if userdoc
 * \fn MB_SetSyncPattern(MBt_Board mb, unsigned int *sync_matrix)
 * \ingroup FUNC
 * \brief Sets sync pattern of the Message Board
 * \param[in] mb Message Board handle
 * \param[in] sync_matrix Integer array representing board communication matrix
 * 
 * Sets the access pattern of the board to allow the board synchronisation 
 * process to be optimised.
 * 
 * This routine is collective and must be called on all MPI processes.
 * However, only the master node (MPI rank == 0) needs to provide a valid
 * \c sync_matrix. The \c sync_matrix parameter will be ignored on all
 * other nodes.
 * 
 * The \c sync_matrix array must be an element count equal to the square of
 * the number of nodes. It is the users responsibility to provide a non-NULL
 * \c sync_matrix which points to an array of apropriate size. 
 * 
 * \warning If an invalid \c sync_matrix is provided by the master node, the 
 * routine may terminate or return errorneously, leaving the other nodes 
 * waiting for further instrustions from the master node hence causing a 
 * deadlock. 
 * 
 * The \c sync_matrix will be processed as an NxN matrix (where N is the number
 * of nodes), whereby the row \c i will represent the amount of communication
 * from all node to node \c i. A zero value will indicate no communication.
 * 
 * When a node does not read from any proc including itself (all zeros in 
 * row \c i), it will be set to a non-reader and all \c MB_Iterator_*() 
 * routines will be disabled.
 * 
 * Similarly, when a node does not send to any other proc including itself, 
 * (add zeros in column \c i) it will be set to a non-writer and 
 * MB_AddMessage() will be disabled.
 * 
 * This routine can only be called when the message board is empty and
 * not locked.
 * 
 * \warning It is recommended that you never call this routine when there
 * any synchronisation in progress. MB_SetSyncPattern() calls MPI routines
 * which may interfere with the synchronisation process if the underlying
 * MPI library is not thread compliant.
 * 
 * Possible return codes:
 *  - ::MB_SUCCESS
 *  - ::MB_ERR_INVALID (\c is null or invalid, or \c sync_matrix is null)
 *  - ::MB_ERR_MEMALLOC (unable to allocate required memory)
 *  - ::MB_ERR_LOCKED (\c mb is locked by another process)
 *  - ::MB_ERR_MPI (error when calling MPI routines)
 *  - ::MB_ERR_NOTREADY (board is not empty)
 * 
 * Usage example:
 * (to be included)
 * \endif
 */
 
/*!\if userdoc
 * \fn MB_AddMessage(MBt_Board mb, void *msg)
 * \ingroup FUNC
 * \brief Adds a message to the Message Board
 * \param[in] mb Message Board handle
 * \param[in] msg Address of the message to be added
 * 
 * Messages added to the board must be of the size specified
 * during the creation of the board. Adding messages of a different size
 * may not cause an error code to be returned, but will lead to unexpected
 * behavior and possible segmentation faults.
 * 
 * The message data addressed by \c msg is cloned and stored in the message 
 * board. Users are free to modify, reuse, or deallocate their copy of the 
 * message after this routine has completed.
 *
 * It this routine returns with an error, the access mode of \c mb will 
 * remain unchanged.
 * 
 * Possible return codes:
 *  - ::MB_SUCCESS
 *  - ::MB_ERR_INVALID (\c mb is null or invalid)
 *  - ::MB_ERR_MEMALLOC (unable to allocate required memory)
 *  - ::MB_ERR_LOCKED (\c mb is locked by another process)
 *  - ::MB_ERR_INTERNAL (internal error, possibly a bug)
 *  - ::MB_ERR_DISABLED (access mode of board set to non-writeable)
 * 
 * Usage example:
 * \include ex_mb_addmessage.c
 * \endif
 */

/*!\if userdoc
 * \fn MB_Clear(MBt_Board mb)
 * \ingroup FUNC
 * \brief Clears the Message Board
 * \param[in] mb Message Board handle
 * 
 * Deletes all messages from the board. The board can be reused
 * for adding more messages of the same type.
 * 
 * Once a board is cleared, all Iterators associated with the board is no longer
 * valid and has to be recreated. It is the users' responsibility to ensure 
 * that invalidated Iterators are never used.
 * 
 * MB_Clear() can be asked not to deallocate memory. The allocated memory 
 * will then be reuse when the board is later populated. This therefore 
 * increases the amount of memory used by the simulation in exchange for 
 * a shorter runtime. This can ge done by setting the following
 * environment variable: <b><tt>MBOARD_MEMPOOL_RECYCLE=1</tt></b>
 *  
 * 
 * Possible return codes:
 *  - ::MB_SUCCESS
 *  - ::MB_ERR_INVALID (\c mb is null or invalid)
 *  - ::MB_ERR_LOCKED (\c mb is locked by another process)
 *  - ::MB_ERR_INTERNAL (internal error, possibly a bug)
 * 
 * Usage example:
 * \include ex_mb_clear.c
 * \endif
 */

/*!\if userdoc
 * \fn MB_Delete(MBt_Board *mb_ptr)
 * \ingroup FUNC
 * \brief Deletes a Message Board
 * \param[in,out] mb_ptr Address of Message Board handle
 * 
 * Upon successful deletion, the handle referenced by \c mb_ptr will be set 
 * to ::MB_NULL_MBOARD.
 * 
 * If an error occurs, this routine will return an error code, and \c mb_ptr 
 * will remain unchanged.
 * 
 * If a null board (::MB_NULL_MBOARD) is given, the routine will return 
 * immediately with ::MB_SUCCESS
 * 
 * Once a board is deleted, all Iterators associated with the board is no longer
 * valid. It is the users' responsibility to ensure that invalidated Iterators 
 * are never used.
 * 
 * 
 * Possible return codes:
 *  - ::MB_SUCCESS
 *  - ::MB_ERR_INVALID (\c mb is invalid)
 *  - ::MB_ERR_LOCKED (\c mb is locked by another process)
 *  - ::MB_ERR_INTERNAL (internal error, possibly a bug)
 * 
 * Usage example:
 * \include ex_mb_delete.c
 * \endif
 */

/*!\if userdoc
 * \fn MB_Iterator_Create(MBt_Board mb, MBt_Iterator *itr_ptr)
 * \ingroup FUNC
 * \brief Creates a new Iterator for accessing messages in board \c mb
 * \param[in] mb Message Board handle
 * \param[out] itr_ptr Address of Iterator Handle
 * 
 * Upon successful creation of the Iterator, the routine  
 * returns a handle to the Iterator via \c itr_ptr .
 *  
 * Attempts to create an Iterator against a null board (::MB_NULL_MBOARD) will 
 * result in an ::MB_ERR_INVALID error.
 * 
 * If this routine returns with an error, \c itr_ptr will remain unchanged.
 * 
 * \warning The Iterator will remain valid as long as the board it was created for
 * is not modified, cleared or deleted. Reading messages from an invalid 
 * Iterator will lead to undefined behaviour and possible segmentation 
 * faults. It is the users' responsibility to ensure that only valid Iterators 
 * are used.
 * 
 * Possible return codes:
 *  - ::MB_SUCCESS
 *  - ::MB_ERR_INVALID (\c mb is null or invalid)
 *  - ::MB_ERR_LOCKED (\c mb is locked by another process)
 *  - ::MB_ERR_MEMALLOC (unable to allocate required memory)
 *  - ::MB_ERR_OVERFLOW (too many Iterators created)
 *  - ::MB_ERR_INTERNAL (internal error, possibly a bug)
 *  - ::MB_ERR_DISABLED (access mode of board set to non-readable)
 * 
 * Usage example:
 * \include ex_mb_it_create.c
 * \endif
 */

/*!\if userdoc
 * \fn MB_Iterator_CreateSorted(MBt_Board mb, MBt_Iterator *itr_ptr, int (*cmpFunc)(const void *msg1, const void *msg2))
 * \ingroup FUNC
 * \brief Creates a new Iterator for accessing sorted messages in board \c mb
 * \param[in] mb Message Board handle
 * \param[out] itr_ptr Address of Iterator Handle
 * \param[in] cmpFunc Pointer to user-defined comparison function
 * 
 * Creates a new Iterator for accessing messages in board \c mb, and 
 * returns a handle to the iterator via \c itr_ptr. This Iterator will allow 
 * users to retrieve ordered messages from \c mb without modifying the board
 * itself.
 * 
 * The user-defined comparison function (\c cmpFunc) must return an integer 
 * less than, equal to, or greater than zero if the first message is 
 * considered to be respectively less than, equal to, or greater than the 
 * second. In short:
 *  - <tt>0 if (msg1 == msg2)</tt>
 *  - <tt>< 0 if (msg1 < msg2)</tt>
 *  - <tt>> 0 if (msg1 > msg2)</tt>
 *  
 * If two members compare as equal, their order in the sorted Iterator is undefined.
 * 
 * Attempts to create an Iterator against a null board (::MB_NULL_MBOARD) will 
 * result in an ::MB_ERR_INVALID error.
 * 
 * If this routine returns with an error, \c itr_ptr will remain unchanged.
 * 
 * \warning The Iterator will remain valid as long as the board it was created for
 * is not modified, cleared or deleted. Reading messages from an invalid 
 * Iterator will lead to undefined behaviour and possible segmentation 
 * faults. It is the users' responsibility to ensure that Iterators are
 * not invalidated before they are used.
 * 
 * Possible return codes:
 *  - ::MB_SUCCESS
 *  - ::MB_ERR_INVALID (\c mb is null or invalid)
 *  - ::MB_ERR_LOCKED (\c mb is locked by another process)
 *  - ::MB_ERR_MEMALLOC (unable to allocate required memory)
 *  - ::MB_ERR_OVERFLOW (too many Iterators created)
 *  - ::MB_ERR_INTERNAL (internal error, possibly a bug)
 *  - ::MB_ERR_DISABLED (access mode of board set to non-readable)
 * 
 * Usage example:
 * \include ex_mb_it_create_s.c
 * \endif
 */

/*!\if userdoc
 * \fn MB_Iterator_CreateFiltered(MBt_Board mb, MBt_Iterator *itr_ptr, int (*filterFunc)(const void *msg, const void *params), void *filterFuncParams )
 * \ingroup FUNC
 * \brief Creates a new Iterator for accessing a selection of messages 
 *        in board \c mb 
 * \param[in] mb Message Board handle
 * \param[out] itr_ptr Address of Iterator Handle
 * \param[in] filterFunc Pointer to user-defined filter function
 * \param[in] filterFuncParams Pointer to input data that will be passed into \c filterFunc 
 * 
 * Creates a new Iterator for accessing messages in board \c mb, and 
 * returns a handle to the iterator via \c itr_ptr. This Iterator will allow 
 * users to retrieve a filtered selection of messages from \c mb without modifying the board
 * itself.
 * 
 * The user-defined filter function (\c filterFunc) must return \c 0 if a message is to be
 * rejected by the filter, or \c 1 if it is to be accepted.
 * 
 * The \c filterFuncParam argument allows users to pass on additional information
 * to \c filterFunc (see example code below). Users may use\c NULL in place of 
 * \c filterFuncParam if \c filterFunc does not require additional information.
 * 
 * Attempts to create an Iterator against a null board (::MB_NULL_MBOARD) will 
 * result in an ::MB_ERR_INVALID error.
 * 
 * If this routine returns with an error, \c itr_ptr will remain unchanged.
 * 
 * \warning The Iterator will remain valid as long as the board it was created for
 * is not modified, cleared or deleted. Reading messages from an invalid 
 * Iterator will lead to undefined behaviour and possible segmentation 
 * faults. It is the users' responsibility to ensure that Iterators are
 * not invalidated before they are used.
 * 
 * Possible return codes:
 *  - ::MB_SUCCESS
 *  - ::MB_ERR_INVALID (\c mb is null or invalid)
 *  - ::MB_ERR_LOCKED (\c mb is locked by another process)
 *  - ::MB_ERR_MEMALLOC (unable to allocate required memory)
 *  - ::MB_ERR_OVERFLOW (too many Iterators created)
 *  - ::MB_ERR_INTERNAL (internal error, possibly a bug)
 *  - ::MB_ERR_DISABLED (access mode of board set to non-readable)
 * 
 * Usage example:
 * \include ex_mb_it_create_f.c
 * \endif
 */

/*!\if userdoc
 * \fn MB_Iterator_CreateFilteredSorted(MBt_Board mb, MBt_Iterator *itr_ptr, int (*filterFunc)(const void *msg, const void *params), void *filterFuncParams, int (*cmpFunc)(const void *msg1, const void *msg2))
 * \ingroup FUNC
 * \brief Instantiates a new Iterator for accessing a sorted selection of 
 *        messages in board \c mb 
 * \param[in] mb Message Board handle
 * \param[out] itr_ptr Address of Iterator Handle
 * \param[in] filterFunc Pointer to user-defined filter function
 * \param[in] filterFuncParams Pointer to input data that will be passed into \c filterFunc 
 * \param[in] cmpFunc Pointer to user-defined compariosn function
 *  
 * Creates a new Iterator for accessing messages in board \c mb, and 
 * returns a handle to the iterator via \c itr_ptr. This Iterator will allow 
 * users to retrieve a filtered selection of ordered messages from \c mb 
 * without modifying the board itself.
 * 
 * The user-defined filter function (\c filterFunc) must return \c 0 if a message is to be
 * rejected by the filter, or \c 1 if it is to be accepted.
 * 
 * The \c filterFuncParam argument allows users to pass on additional information
 * to \c filterFunc (see example code below). Users may use\c NULL in place of 
 * \c filterFuncParam if \c filterFunc does not require additional information.
 * 
 * The user-defined comparison function (\c cmpFunc) must return an integer 
 * less than, equal to, or greater than zero if the first message is 
 * considered to be respectively less than, equal to, or greater than the 
 * second. In short:
 *  - <tt>0 if (msg1 == msg2)</tt>
 *  - <tt>\< 0 if (msg1 \< msg2)</tt>
 *  - <tt>\> 0 if (msg1 \> msg2)</tt>
 * 
 * Attempts to create an Iterator against a null board (::MB_NULL_MBOARD) will 
 * result in an ::MB_ERR_INVALID error.
 * 
 * If this routine returns with an error, \c itr_ptr will remain unchanged.
 * 
 * \warning The Iterator will remain valid as long as the board it was created for
 * is not modified, cleared or deleted. Reading messages from an invalid 
 * Iterator will lead to undefined behaviour and possible segmentation 
 * faults. It is the users' responsibility to ensure that Iterators are
 * not invalidated before they are used.
 *
 * Possible return codes:
 *  - ::MB_SUCCESS
 *  - ::MB_ERR_INVALID (\c mb is null or invalid)
 *  - ::MB_ERR_LOCKED (\c mb is locked by another process)
 *  - ::MB_ERR_MEMALLOC (unable to allocate required memory)
 *  - ::MB_ERR_OVERFLOW (too many Iterators created)
 *  - ::MB_ERR_INTERNAL (internal error, possibly a bug)
 *  - ::MB_ERR_DISABLED (access mode of board set to non-readable)
 * 
 * Usage example:
 * \include ex_mb_it_create_fs.c
 * \endif
 */

/*!\if userdoc
 * \fn MB_Iterator_Delete(MBt_Iterator *itr_ptr)
 * \ingroup FUNC
 * \brief Deletes an Iterator
 * \param[in,out] itr_ptr Address of Iterator Handle
 * 
 * Upon successful deletion, the handle referenced by \c itr_ptr will be set 
 * to ::MB_NULL_ITERATOR.
 * 
 * If an error occurs, \c itr_ptr will remain unchanged.
 * 
 * If a null Iterator (::MB_NULL_ITERATOR) is passed in, the routine will return 
 * immediately with ::MB_SUCCESS
 * 
 * 
 * Possible return codes:
 *  - ::MB_SUCCESS
 *  - ::MB_ERR_INVALID (\c itr is invalid)
 *  - ::MB_ERR_INTERNAL (internal error, possibly a bug)
 * 
 * Usage example:
 * \include ex_mb_it_delete.c
 * \endif
 */

/*!\if userdoc
 * \fn MB_Iterator_GetMessage(MBt_Iterator itr, void **msg_ptr)
 * \ingroup FUNC
 * \brief Returns next available message from Iterator
 * \param[in] itr Iterator Handle
 * \param[out] msg_ptr Address where pointer to message will be written to
 * 
 * After a successful call to the routine, \c msg_ptr will be assigned with 
 * a pointer to a newly allocated memory block containing the message 
 * data. It is the user's responsibility to free the memory associated with the 
 * returned msg.
 *
 * When there are no more messages to return, \c msg_ptr will be assigned with
 * \c NULL and the routine shall complete with the ::MB_SUCCESS return code.
 *
 * Any attempts to retrieve a message from a null Iterator (::MB_NULL_ITERATOR) will 
 * result in an ::MB_ERR_INVALID error.
 * 
 * In the event of an error, msg will be assigned \c NULL and the routine shall
 * return with an appropriate error code.
 * 
 * \warning If the given Iterator is invalidated due to a deletion or clearance 
 * of the target board, calling this routine on the invalid board may result in
 * either an undefined block of data or a segmentation fault.
 * 
 * Possible return codes:
 *  - ::MB_SUCCESS
 *  - ::MB_ERR_INVALID (\c itr is null of invalid)
 *  - ::MB_ERR_MEMALLOC (unable to allocate required memory)
 * 
 * Usage example:
 * \include ex_mb_it_getmessage.c
 * \endif
 */

/*!\if userdoc
 * \fn MB_Iterator_Rewind(MBt_Iterator itr)
 * \ingroup FUNC
 * \brief Rewinds an Iterator
 * \param[in] itr Iterator Handle
 * 
 * Resets the internal counters such that the next MB_Iterator_GetMessage() 
 * call on the given Iterator will obtain the first message in the list 
 * (or \c NULL if the Iterator is empty).
 * 
 * Rewinding a null Iterator (::MB_NULL_ITERATOR) will result in an 
 * ::MB_ERR_INVALID error.
 * 
 * Possible return codes:
 *  - ::MB_SUCCESS
 *  - ::MB_ERR_INVALID (\c itr is null or invalid)
 * 
 * Usage example:
 * \include ex_mb_it_rewind.c
 * \endif
 */

/*!\if userdoc
 * \fn MB_Iterator_Randomise(MBt_Iterator itr)
 * \ingroup FUNC
 * \brief Randomises the order of entries in an Iterator
 * \param[in] itr Iterator Handle
 * 
 * Apart from randomising the order of entries in the Iterator, this routine 
 * will also reset the internal counters leading to an effect similar to that
 * of MB_Iterator_Rewind().
 * 
 * Randomising a null Iterator (::MB_NULL_ITERATOR) will result in an 
 * ::MB_ERR_INVALID error.
 * 
 * Possible return codes:
 *  - ::MB_SUCCESS
 *  - ::MB_ERR_INVALID (\c itr is null or invalid)
 *  - ::MB_ERR_INTERNAL (internal error, possibly a bug)
 * 
 * Usage example:
 * \include ex_mb_it_randomise.c
 * \endif
 */

/*!\if userdoc
 * \fn MB_SyncStart(MBt_Board mb)
 * \ingroup FUNC
 * \brief Synchronises the content of the board across all processes
 * \param[in] mb Message Board Handle
 * 
 * This is a non-blocking routine which returns immediately after 
 * locking the message board and intialising the synchronisation 
 * process. The board should not be modified, cleared, or deleted 
 * until the synchronisation process is completed using
 * MB_SyncComplete() (or until MB_SyncTest() results in a ::MB_TRUE
 * flag).
 * 
 * In the serial version, this routine will do nothing apart from 
 * locking the message board. 
 * 
 * Synchronisation of a null board (::MB_NULL_MBOARD) is valid, and will 
 * return immediately with ::MB_SUCCESS
 * 
 * \note Multiple synchronisations of a board is <i>supported</i> but perhaps
 * not in the way that you might expect. Subsequent synchronisations will only 
 * consider messages that were added after the previous synchronisation, which
 * means that messages that were excluded (by filters) in previous syncs will
 * not be considered in following ones. 
 * 
 * Possible return codes:
 *  - ::MB_SUCCESS
 *  - ::MB_ERR_INVALID (\c mb is invalid)
 *  - ::MB_ERR_INTERNAL (internal error, possibly a bug)
 *  - ::MB_ERR_LOCKED (\c mb is locked by another process)
 * 
 * Usage example:
 * \include ex_mb_sync.c
 * \endif
 */

/*!\if userdoc
 * \fn MB_SyncTest(MBt_Board mb, int *flag)
 * \ingroup FUNC
 * \brief Inspects the completion status of a board synchronisation
 * \param[in] mb Message Board Handle
 * \param[out] flag address where return value will be written to
 * 
 * This routine is non-blocking, and will return after setting the
 * \c flag value to either ::MB_TRUE or ::MB_FALSE depending on the 
 * synchronisation completion status.
 * 
 * If synchronisation has completed, the ::MB_TRUE flag is returned, 
 * and the board is unlocked. The synchronisation process is considered 
 * to be completed, and users no longer need to call MB_SyncComplete() 
 * on this board.
 * 
 * Testing a null board (::MB_NULL_MBOARD) will always return with 
 * the ::MB_TRUE flag and ::MB_SUCCESS return code.
 * 
 * Testing a board that is not being synchronised is invalid,  
 * and will return with the ::MB_FALSE flag and ::MB_ERR_INVALID 
 * return code.
 * 
 * In the serial version, this routine will always return ::MB_TRUE as
 * synchronisation is assumed to be completed immediately after it started.
 * 
 * Possible return codes:
 *  - ::MB_SUCCESS
 *  - ::MB_ERR_INVALID (\c mb is invalid or not being synchronised)
 *  - ::MB_ERR_INTERNAL (internal error, possibly a bug)
 * 
 * Usage example: see MB_SyncStart()
 * \endif
 */


/*!\if userdoc
 * \fn MB_SyncComplete(MBt_Board mb)
 * \ingroup FUNC
 * \brief Completes the synchronisation of a board
 * \param[in] mb Message Board Handle
 * 
 * This routine will block until the synchronisation of the board has
 * completed. Upon successful execution of this routine, the board
 * will be unlocked and ready for access.
 * 
 * In the serial version, this routine will do nothing apart from 
 * unlocking the message board. 
 * 
 * Synchronisation of a null board (::MB_NULL_MBOARD) is valid, and will 
 * return immediately with ::MB_SUCCESS
 * 
 * Completing synchronisation a board that is not being synchronised is invalid,  
 * and will return with the ::MB_ERR_INVALID error code.
 * 
 * Possible return codes:
 *  - ::MB_SUCCESS
 *  - ::MB_ERR_INVALID (\c mb is invalid or not being synchronised)
 *  - ::MB_ERR_INTERNAL (internal error, possibly a bug)
 * 
 * Usage example: see MB_SyncStart()
 * \endif
 */

/*!\if userdoc
 * \fn MB_Filter_Create(MBt_Filter *fh_ptr, int (*filterFunc)(const void *msg, int pid) );
 * \ingroup FUNC
 * \brief Creates a filter object
 * \param[out] fh_ptr Address to write Filter Handle to
 * \param[in] filterFunc Pointer to user-defined function
 * 
 * <i>Introduced in version 0.2.0.</i>
 * 
 * Registers a filter function and returns a handle to the filter via
 * \c ft_ptr. The handle is unique to that function and is recognised across 
 * all processing nodes. 
 * 
 * Registered filters can be assigned to message boards
 * using MB_Filter_Assign() to act as a filtering mechanism when retrieving
 * messages from remote nodes during a synchronisation. This reduces the number of
 * messages that need to be transferred and stored on each node.
 * 
 * If this routine returns with an error, \c fh_ptr will be set to :: MB_NULL_FILTER.
 * 
 * In the parallel debug version, this routine is blocking and will return when 
 * all processes have issued and completed the call. This effectively 
 * synchronises all processing nodes. It is the users' responsibility to ensure 
 * that all processing nodes issue the call (with the same values for \c filterFunc) 
 * to prevent deadlocks.
 * 
 * Possible return codes:
 *  - ::MB_SUCCESS
 *  - ::MB_ERR_INVALID (\c filterFunc is NULL)
 *  - ::MB_ERR_MEMALLOC (unable to allocate required memory)
 *  - ::MB_ERR_OVERFLOW (Too many functions registered)
 *  - ::MB_ERR_INTERNAL (Internal error, possibly a bug)
 * 
 * Usage example:
 * \include ex_mb_filter.c
 * \endif
 */

/*!\if userdoc
 * \fn MB_Filter_Assign(MBt_Board mb, MBt_Filter fh);
 * \ingroup FUNC
 * \brief Assigns a filter handle to a message board
 * \param[in] mb Message Board Handle
 * \param[in] fh Filter Handle
 * 
 * <i>Introduced in version 0.2.0.</i>
 * 
 * This routine assigns a registered filter to a Message Board. The associated
 * filter function will act as a filtering mechanism when retrieving
 * messages from remote nodes during a synchronisation. This reduces the number of
 * messages that need to be transferred and stored on each node.
 * 
 * For efficiency, boards must be assigned with the same \c fh on all
 * MPI processes. It is left to the user to ensure that this is so.
 * 
 * \c fh can be ::MB_NULL_FILTER, in which case \c mb will be deassociated with any 
 * function that it was previously assigned with.
 * 
 * Possible return codes:
 *  - ::MB_SUCCESS
 *  - ::MB_ERR_INVALID (\c mb is NULL or invalid, or \c fh is invalid)
 *  - ::MB_ERR_LOCKED (\c mb is locked by another process)
 * \endif
 * 
 * Usage example: see MB_Filter_Create()
 */

/*!\if userdoc
 * \fn MB_Filter_Delete(MBt_Filter *fh_ptr);
 * \ingroup FUNC
 * \brief Deallocates a registered function
 * \param[in,out] fh_ptr Address of Filter Handle
 * 
 * <i>Introduced in version 0.2.0.</i>
 * 
 * The filter function associated with \c fh_ptr will be deregistered, 
 * and \c fh_ptr will be set to ::MB_NULL_FILTER.  
 * 
 * Deleting a filter that is assigned to a board will result in an error
 * if the board is synchronised. It is the users' responsibility to ensure that
 * this does not happen. 
 * 
 * If an invalid handle is give, the routine will end with ::MB_ERR_INVALID 
 * and \c fh_ptr will not be modified.
 * 
 * If ::MB_NULL_FILTER is entered via \c fh_ptr, the routine will end 
 * immediately with ::MB_SUCCESS.
 * 
 * Possible return codes:
 *  - ::MB_SUCCESS
 *  - ::MB_ERR_INVALID (\c fh_ptr is NULL or invalid)
 * \endif
 * 
 * Usage example: see MB_Filter_Create()
 */


/*!\if userdoc
 * \fn MB_IndexMap_Create(MBt_IndexMap *im_ptr, const char *name)
 * \ingroup FUNC
 * \brief Instantiates a new Index Map object
 * \param[in] name Unique string identifying the map (max of 127 chars)
 * \param[out] im_ptr Address of Index Map handle
 * 
 * <i>Introduced in version 0.2.0.</i>
 * 
 * Creates a new Index Map and returns a handle to the map via \c im_ptr .
 * 
 * \c name should be a string that uniquely identifies the map and can
 * contain up to 127 characters. If the given string is longer than 127
 * characters the routine will quit and return with ::MB_ERR_OVERFLOW.
 * 
 * In the parallel debug version, this routine is blocking and will return when 
 * all processes have issued and completed the call. This effectively 
 * synchronises all processes. It is the users' responsibility to ensure 
 * that all processes issue the call (in the same order if multiple maps are
 * created).
 * 
 * 
 * If this routine returns with an error, \c im_ptr will be set to ::MB_NULL_INDEXMAP.
 * 
 * Possible return codes:
 *  - ::MB_SUCCESS
 *  - ::MB_ERR_MEMALLOC (unable to allocate required memory)
 *  - ::MB_ERR_OVERFLOW (too many maps created)
 *  - ::MB_ERR_INTERNAL (internal error, possibly a bug)
 *  - ::MB_ERR_DUPLICATE (\c name already exists)
 *  - ::MB_ERR_INVALID (\c name is NULL)
 *  - ::MB_ERR_OVERFLOW (\c name is too long)
 *  - ::MB_ERR_ENV (Message Board environment not yet initialised)
 * 
 * Usage example:
 * \include ex_mb_indexmap.c
 * \endif
 */

/*!\if userdoc
 * \fn MB_IndexMap_Delete(MBt_IndexMap *im_ptr)
 * \ingroup FUNC
 * \brief Deletes an Index Map
 * \param[in,out] im_ptr Address of Index Map handle
 * 
 * <i>Introduced in version 0.2.0.</i>
 * 
 * Upon successful deletion, the handle referenced by \c im_ptr will be set 
 * to ::MB_NULL_INDEXMAP.
 * 
 * If an error occurs, this routine will return an error code and \c im_ptr 
 * will remain unchanged.
 * 
 * If a null board (::MB_NULL_INDEXMAP) is given, the routine will return 
 * immediately with ::MB_SUCCESS
 * 
 * 
 * Possible return codes:
 *  - ::MB_SUCCESS
 *  - ::MB_ERR_INVALID (\c im is invalid)
 *  - ::MB_ERR_INTERNAL (internal error, possibly a bug)
 * 
 * Usage example: see MB_IndexMap_Create()
 * \endif
 */

/*!\if userdoc
 * \fn MB_IndexMap_AddEntry(MBt_IndexMap im, int value)
 * \ingroup FUNC
 * \brief Adds an entry into the Index Map
 * \param[in] im Index Map handle
 * \param[in] value Integer value of entry to add into the map
 * 
 * <i>Introduced in version 0.2.0.</i>
 * 
 * Entry will be added to the local map. In the parallel version, this entry
 * will be searchable on other processors after MB_IndexMap_Sync() is called.
 * 
 * Adding an entry that already exists will have no effect on the map and the
 * routine will return successfully.
 * 
 * Possible return codes:
 *  - ::MB_SUCCESS
 *  - ::MB_ERR_INVALID (\c im is null or invalid)
 *  - ::MB_ERR_MEMALLOC (unable to allocate required memory)
 *  - ::MB_ERR_INTERNAL (internal error, possibly a bug)
 * 
 * Usage example: see MB_IndexMap_Create()
 * \endif
 */

/*!\if userdoc
 * \fn MB_IndexMap_Sync(MBt_IndexMap im)
 * \ingroup FUNC
 * \brief Distributes/gathers the map content across/from all processors
 * \param[in] im Index Map handle
 * 
 * <i>Introduced in version 0.2.0.</i>
 * 
 * In the serial library, this routine does nothing and returns immediately 
 * with ::MB_SUCCESS. It will however return with an appropriate error code
 * if an invalid or null map is given.
 * 
 * In parallel, this routine is a blocking and collective operation. It is the
 * users' responsibility to ensure that the routine is called on all processors
 * to avoid deadlocks.
 * 
 * Contents of the map is distributed across all processors such that every 
 * processor will be able to determine if an entry exists in a map of any
 * other processor using the MB_IndexMap_MemberOf() routine.
 * 
 * This routine should be called after all entries are added to the map (using
 * MB_IndexMap_AddEntry()) and before and queries are made (using 
 * MB_IndexMap_MemberOf()).
 * 
 * \warning This routine calls MPI Routines and should therefore never be called
 * when there are any Message Board syncs in progress as this will cause
 * problems with MPI Libraries that do not support full threading.
 * 
 * Possible return codes:
 *  - ::MB_SUCCESS
 *  - ::MB_ERR_INVALID (\c im is null or invalid)
 *  - ::MB_ERR_MEMALLOC (unable to allocate required memory)
 *  - ::MB_ERR_INTERNAL (internal error, possibly a bug)
 *  - ::MB_ERR_MPI (Error returned from MPI calls, possibly a bug)
 * 
 * Usage example: see MB_IndexMap_Create()
 * \endif
 */

/*!\if userdoc
 * \fn MB_IndexMap_MemberOf(MBt_IndexMap im, int pid, int value)
 * \ingroup FUNC
 * \brief Query the map to determine if a value exists on a particular processor
 * \param[in] im Index Map handle
 * \param[in] pid Target processor ID
 * \param[in] value Value of entry to query for
 * 
 * <i>Introduced in version 0.2.0.</i>
 * 
 * Returns ::MB_TRUE or ::MB_FALSE depending on whether \c value exists in
 * the map of processor with ID \c pid. 
 * 
 * MB_IndexMap_Sync() must be called on the map before this routine can be used.
 * 
 * In the serial library, \c pid is ignored and the call to MB_IndexMap_Sync() 
 * is not compulsory but advisable.
 * 
 * \warning This is the only IndexMap routine that will be called very 
 * frequently during the simulation. We want it to be fast fast fast, 
 * so all checks are only done in debug mode!!! It is therefore crucial 
 * that end-users always test their code with the debug version of 
 * libmboard before using it in earnest. 
 * 
 * 
 * Possible return codes:
 *  - ::MB_TRUE (\c value exists in the specified map)
 *  - ::MB_FALSE (\c value does not exist in the specified map)
 *  - ::MB_ERR_NOTREADY (map has not been synchronised using MB_IndexMap_Sync())
 *  - ::MB_ERR_INVALID (\c pid or \c im is invalid or null)
 *  - ::MB_ERR_INTERNAL (internal error, possibly a bug)
 * 
 * Usage example: see MB_IndexMap_Create()
 * \endif
 */

/*!\if userdoc
 * \page tuning Tuning libmboard using environment variables
 * 
 * The behaviour and configuration parameters of libmboard can be modified by 
 * setting the relevant environment variables.
 * 
 * \section toc Table of Contents
 * -# \ref tune_mem
 *  - \ref mempool_recycle
 *  - \ref mempool_blocksize
 * -# \ref tune_comm
 *  - \ref comm_protocol
 *
 * <hr>
 * 
 * \section tune_mem Environment variables to tune memory usage
 * 
 * The following environment variables can be used to influence the memory
 * usage of boards.
 * 
 * \subsection mempool_recycle MBOARD_MEMPOOL_RECYCLE (default: OFF)
 * 
 * Use this variable to recycle memory used by the message board. When this 
 * is enabled MB_Clear() will reset the internal cursors but leave the
 * used memory unallocated. 
 * 
 * Enabling this feature will reduce the time taken to deallocate (and 
 * reallocate) memory used to store messages in boards. It will however lead
 * to higher memory usage.
 * 
 * \c MBOARD_MEMPOOL_RECYCLE can be set to "1", "ON", "YES", or "TRUE" to 
 * enable this feature.
 * 
 * \c MBOARD_MEMPOOL_RECYCLE can be set to "0", "OFF", "NO", or "FALSE" to 
 * disable this feature.
 * 
 * \subsection mempool_blocksize MBOARD_MEMPOOL_BLOCKSIZE (default: 512)
 * 
 * Use this variable to specify the size of each memory block allocated.
 * 
 * Messages boards allocate memory in large chunks to avoid having to allocate
 * small fragments of memory for each message. This variable controls the size 
 * of each allocation. For example, if \c MBOARD_MEMPOOL_BLOCKSIZE=1024 memory 
 * is allocated such that 1024 messages can be added to the board before more
 * memory needs to be allocated.
 * 
 * The value assigned to \c MBOARD_MEMPOOL_BLOCKSIZE must be between 10 to 
 * 1,000,000. If an invalid value is set to the environment variable, or if
 * the variable is not defined, the default value will be used.
 * 
 * \section tune_comm Environmen variables to tune communication between boards
 * 
 * The following environment variables can be used to influence the
 * communication strategies adopted when synchronising message boards.
 * 
 * \subsection comm_protocol MBOARD_COMM_PROTOCOL (default: "HANDSHAKE")
 * 
 * Use this variable to switch to a communication protocol that will suit
 * your hardware setup and underlying MPI implementation.
 * 
 * \c MBOARD_COMM_PROTOCOL can be set to one of the following protocols:
 * 
 *  - "HANDSHAKE" : ... more info here ... 
 *  - "OLD" : ... more info here ... 
 * 
 * \endif
 */
#endif /*MBOARD_H_*/
