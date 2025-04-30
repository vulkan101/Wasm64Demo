using System.Reflection;
using System.Runtime.InteropServices;

namespace WebViewer
{
    public static class TestAllocationInterop
    {        
        public static void Initialise()
        {            
		}
        public static void Allocate(int numGB)
        {
            TestAllocation(numGB);
        }
     
        public static void Teardown()
        {            
            
        }

		[DllImport("TestAllocation")]
		[DefaultDllImportSearchPaths(DllImportSearchPath.AssemblyDirectory)]
		private static extern void TestAllocation(int numGB);
	}
}