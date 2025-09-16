program same_host
    use mpi
    use App, only: App_samehost
    implicit none

    integer :: ierr
    logical :: same = .false.

    call MPI_Init(ierr)
    same = App_samehost(MPI_COMM_WORLD)
    call MPI_Finalize(ierr)

    if (same) then
        print *, "All MPI processes are on the same host"
        stop 0
    else
        print *, "All MPI processes are not the same host"
        stop 1
    endif
end program