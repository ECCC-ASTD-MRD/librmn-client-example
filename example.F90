module librmn
    use iso_c_binding
    implicit none

    interface
        subroutine print_librmn_version() bind(C, name = 'print_rmn_version')
        end subroutine print_librmn_version
    end interface
end module


program hello
    use librmn
    implicit none

    call print_librmn_version()
end program hello
