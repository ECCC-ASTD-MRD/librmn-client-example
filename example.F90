module librmn
    use iso_c_binding
    implicit none

    interface
        subroutine print_build_info() bind(C, name = 'rmn_print_build_info')
        end subroutine
    end interface
end module


program hello
    use librmn
    implicit none

    call print_build_info()
end program
