void func(int i, long j)
{
    (void)i;
    (void)j;//no -Wold-style-cast warning
}
int main()
{
    func(0,0);
    return 0;
}
