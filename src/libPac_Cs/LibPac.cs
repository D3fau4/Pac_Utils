namespace libPac_Cs
{
    public static partial class LibPac
    {
#if UNITY_STANDALONE_LINUX
        internal const string DllName = "libNep";
#else
        internal const string DllName = "libPac";
#endif
    }
}
